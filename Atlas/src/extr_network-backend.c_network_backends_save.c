#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  default_file; TYPE_6__* raw_pwds; TYPE_6__* raw_ips; int /*<<< orphan*/  backends_mutex; TYPE_6__* backends; } ;
typedef  TYPE_3__ network_backends_t ;
struct TYPE_21__ {scalar_t__ type; TYPE_2__* addr; } ;
typedef  TYPE_4__ network_backend_t ;
typedef  scalar_t__ guint ;
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_24__ {int /*<<< orphan*/  message; } ;
struct TYPE_23__ {scalar_t__ len; } ;
struct TYPE_22__ {scalar_t__ len; char* str; } ;
struct TYPE_19__ {TYPE_1__* name; } ;
struct TYPE_18__ {int /*<<< orphan*/ * str; } ;
typedef  TYPE_5__ GString ;
typedef  TYPE_6__ GPtrArray ;
typedef  int /*<<< orphan*/  GKeyFile ;
typedef  TYPE_7__ GError ;

/* Variables and functions */
 scalar_t__ BACKEND_TYPE_RO ; 
 scalar_t__ BACKEND_TYPE_RW ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  G_KEY_FILE_KEEP_COMMENTS ; 
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_free (TYPE_7__*) ; 
 scalar_t__ g_file_set_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__**) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_key_file_free (int /*<<< orphan*/ *) ; 
 scalar_t__ g_key_file_load_from_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__**) ; 
 int /*<<< orphan*/ * g_key_file_new () ; 
 int /*<<< orphan*/  g_key_file_set_list_separator (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  g_key_file_set_value (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/ * g_key_file_to_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_message (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ ) ; 
 void* g_ptr_array_index (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  g_string_append (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_append_c (TYPE_5__*,char) ; 
 int /*<<< orphan*/  g_string_append_printf (TYPE_5__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_free (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* g_string_new (int /*<<< orphan*/ *) ; 

int network_backends_save(network_backends_t *bs) {
	GKeyFile *keyfile = g_key_file_new();
	g_key_file_set_list_separator(keyfile, ',');
	GError *gerr = NULL;

	if (FALSE == g_key_file_load_from_file(keyfile, bs->default_file, G_KEY_FILE_KEEP_COMMENTS, &gerr)) {
		g_critical("%s: g_key_file_load_from_file: %s", G_STRLOC, gerr->message);
		g_error_free(gerr);
		g_key_file_free(keyfile);
		return -1;
	}

	GString *master = g_string_new(NULL);
	GString *slave  = g_string_new(NULL);
	guint i;
	GPtrArray *backends = bs->backends;

	g_mutex_lock(bs->backends_mutex);
	guint len = backends->len;
	for (i = 0; i < len; ++i) {
		network_backend_t *backend = g_ptr_array_index(backends, i);
		if (backend->type == BACKEND_TYPE_RW) {
			g_string_append_printf(master, ",%s", backend->addr->name->str);
		} else if (backend->type == BACKEND_TYPE_RO) {
			g_string_append_printf(slave, ",%s", backend->addr->name->str);
		}
	}
	g_mutex_unlock(bs->backends_mutex);

	if (master->len != 0) {
		g_key_file_set_value(keyfile, "mysql-proxy", "proxy-backend-addresses", master->str+1);
	} else {
		g_key_file_set_value(keyfile, "mysql-proxy", "proxy-backend-addresses", "");
	}
	if (slave->len != 0) {
		g_key_file_set_value(keyfile, "mysql-proxy", "proxy-read-only-backend-addresses", slave->str+1);
	} else {
		g_key_file_set_value(keyfile, "mysql-proxy", "proxy-read-only-backend-addresses", "");
	}

	g_string_free(master, TRUE);
	g_string_free(slave, TRUE);

	GString *client_ips = g_string_new(NULL);
	for (i = 0; i < bs->raw_ips->len; ++i) {
		gchar *client_ip = g_ptr_array_index(bs->raw_ips, i);
		g_string_append_printf(client_ips, ",%s", client_ip);
	}
	if (client_ips->len != 0) {
		g_key_file_set_value(keyfile, "mysql-proxy", "client-ips", client_ips->str+1);
	} else {
		g_key_file_set_value(keyfile, "mysql-proxy", "client-ips", "");
	}
	g_string_free(client_ips, TRUE);

	GString *pwds = g_string_new(NULL);
	for (i = 0; i < bs->raw_pwds->len; ++i) {
		g_string_append_c(pwds, ',');
		gchar *user_pwd = g_ptr_array_index(bs->raw_pwds, i);
		g_string_append(pwds, user_pwd);
	}
	if (pwds->len != 0) {
		g_key_file_set_value(keyfile, "mysql-proxy", "pwds", pwds->str+1);
	} else {
		g_key_file_set_value(keyfile, "mysql-proxy", "pwds", "");
	}
	g_string_free(pwds, TRUE);

	gsize file_size = 0;
	gchar *file_buf = g_key_file_to_data(keyfile, &file_size, NULL);
	if (FALSE == g_file_set_contents(bs->default_file, file_buf, file_size, &gerr)) {
		g_critical("%s: g_file_set_contents: %s", G_STRLOC, gerr->message);
		g_free(file_buf);
		g_error_free(gerr);
		g_key_file_free(keyfile);
		return -1;
	}

	g_message("%s: saving config file succeed", G_STRLOC);
	g_free(file_buf);
	g_key_file_free(keyfile);
	return 0;
}