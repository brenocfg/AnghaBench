#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t* pwd_table_index; int /*<<< orphan*/ ** pwd_table; int /*<<< orphan*/  raw_pwds; } ;
typedef  TYPE_1__ network_backends_t ;
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GString ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int ERR_PWD_DECRYPT ; 
 int ERR_PWD_ENCRYPT ; 
 int PWD_SUCCESS ; 
 int /*<<< orphan*/  copy_pwd ; 
 int /*<<< orphan*/ * decrypt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * encrypt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_atomic_int_set (size_t*,int) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_remove_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_ptr_array_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_strdup_printf (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_proto_password_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

int network_backends_addpwd(network_backends_t *bs, gchar *user, gchar *pwd, gboolean is_encrypt) {
	GString *hashed_password = g_string_new(NULL);
	if (is_encrypt) {
		gchar *decrypt_pwd = decrypt(pwd);
		if (decrypt_pwd == NULL) {
			g_warning("failed to decrypt %s\n", pwd);
			return ERR_PWD_DECRYPT;
		}
		network_mysqld_proto_password_hash(hashed_password, decrypt_pwd, strlen(decrypt_pwd));
		g_free(decrypt_pwd);
		g_ptr_array_add(bs->raw_pwds, g_strdup_printf("%s:%s", user, pwd));
	} else {
		gchar *encrypt_pwd = encrypt(pwd);
		if (encrypt_pwd == NULL) {
			g_warning("failed to encrypt %s\n", pwd);
			return ERR_PWD_ENCRYPT;
		}
		g_ptr_array_add(bs->raw_pwds, g_strdup_printf("%s:%s", user, encrypt_pwd));
		g_free(encrypt_pwd);
		network_mysqld_proto_password_hash(hashed_password, pwd, strlen(pwd));
	}


	gint index = *(bs->pwd_table_index);
	GHashTable *old_table = bs->pwd_table[index];
	GHashTable *new_table = bs->pwd_table[1-index];
	g_hash_table_remove_all(new_table);
	g_hash_table_foreach(old_table, copy_pwd, new_table);
	g_hash_table_insert(new_table, g_strdup(user), hashed_password);
	g_atomic_int_set(bs->pwd_table_index, 1-index);

	return PWD_SUCCESS;
}