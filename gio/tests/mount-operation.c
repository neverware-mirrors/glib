/* GLib testing framework examples and tests
 *
 * Copyright © 2018 Endless Mobile, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Philip Withnall <withnall@endlessm.com>
 */

#include <gio/gio.h>
#include <locale.h>


/* Smoketest for construction of a #GMountOperation. */
static void
test_construction (void)
{
  GMountOperation *op = NULL;

  op = g_mount_operation_new ();
  g_assert_nonnull (op);
  g_assert_true (G_IS_MOUNT_OPERATION (op));
  g_object_unref (op);
}

/* Test the property getters and setters on #GMountOperation work correctly. */
static void
test_properties (void)
{
  GMountOperation *op = NULL;
  gchar *username = NULL;
  gchar *password = NULL;
  gboolean anonymous;
  gchar *domain = NULL;
  GPasswordSave password_save;
  int choice;

  op = g_mount_operation_new ();

  g_object_get (op,
                "username", &username,
                "password", &password,
                "anonymous", &anonymous,
                "domain", &domain,
                "password-save", &password_save,
                "choice", &choice,
                NULL);

  g_assert_cmpstr (username, ==, g_mount_operation_get_username (op));
  g_assert_cmpstr (password, ==, g_mount_operation_get_password (op));
  g_assert_cmpint (anonymous, ==, g_mount_operation_get_anonymous (op));
  g_assert_cmpstr (domain, ==, g_mount_operation_get_domain (op));
  g_assert_cmpint (password_save, ==, g_mount_operation_get_password_save (op));
  g_assert_cmpint (choice, ==, g_mount_operation_get_choice (op));

  g_mount_operation_set_username (op, "username");
  g_assert_cmpstr (g_mount_operation_get_username (op), ==, "username");

  g_mount_operation_set_password (op, "password");
  g_assert_cmpstr (g_mount_operation_get_password (op), ==, "password");

  g_mount_operation_set_anonymous (op, !anonymous);
  g_assert_cmpint (g_mount_operation_get_anonymous (op), ==, !anonymous);

  g_mount_operation_set_domain (op, "domain");
  g_assert_cmpstr (g_mount_operation_get_domain (op), ==, "domain");

  g_mount_operation_set_password_save (op, G_PASSWORD_SAVE_NEVER);
  g_assert_cmpint (g_mount_operation_get_password_save (op), ==, G_PASSWORD_SAVE_NEVER);

  g_mount_operation_set_choice (op, 5);
  g_assert_cmpint (g_mount_operation_get_choice (op), ==, 5);

  g_object_set (op,
                "username", "other-username",
                "password", "other-password",
                "anonymous", FALSE,
                "domain", "other-domain",
                "password-save", G_PASSWORD_SAVE_PERMANENTLY,
                "choice", 4,
                NULL);

  g_free (domain);
  g_free (password);
  g_free (username);
  g_object_unref (op);
}

int
main (int   argc,
      char *argv[])
{
  setlocale (LC_ALL, "");
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/mount-operation/construction", test_construction);
  g_test_add_func ("/mount-operation/properties", test_properties);

  return g_test_run ();
}