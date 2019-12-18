#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t guint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_5__ {int /*<<< orphan*/ * option_grp_name; } ;
typedef  TYPE_1__ chassis_plugin ;
struct TYPE_6__ {size_t len; TYPE_1__** pdata; } ;
typedef  TYPE_2__ GPtrArray ;
typedef  int /*<<< orphan*/  GOptionGroup ;
typedef  int /*<<< orphan*/  GOptionEntry ;
typedef  int /*<<< orphan*/  GOptionContext ;
typedef  int /*<<< orphan*/  GKeyFile ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  chassis_keyfile_resolve_path (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ chassis_keyfile_to_options (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * chassis_plugin_get_options (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_option_context_add_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ g_option_context_parse (int /*<<< orphan*/ *,int*,char***,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_option_group_add_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_option_group_new (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ *) ; 

int chassis_frontend_init_plugins(GPtrArray *plugins,
		GOptionContext *option_ctx,
		int *argc_p, char ***argv_p,
		GKeyFile *keyfile,
		const char *keyfile_section_name,
		const char *base_dir,
		GError **gerr) {
	guint i;

	for (i = 0; i < plugins->len; i++) {
		GOptionEntry *config_entries;
		chassis_plugin *p = plugins->pdata[i];

		if (NULL != (config_entries = chassis_plugin_get_options(p))) {
			gchar *group_desc = g_strdup_printf("%s-module", p->option_grp_name);
			gchar *help_msg = g_strdup_printf("Show options for the %s-module", p->option_grp_name);
			const gchar *group_name = p->option_grp_name;

			GOptionGroup *option_grp = g_option_group_new(group_name, group_desc, help_msg, NULL, NULL);
			g_option_group_add_entries(option_grp, config_entries);
			g_option_context_add_group(option_ctx, option_grp);

			g_free(help_msg);
			g_free(group_desc);

			/* parse the new options */
			if (FALSE == g_option_context_parse(option_ctx, argc_p, argv_p, gerr)) {
				return -1;
			}
	
			if (keyfile) {
				if (chassis_keyfile_to_options(keyfile, keyfile_section_name, config_entries)) {
					return -1;
				}
			}

			/* resolve the path names for these config entries */
			chassis_keyfile_resolve_path(base_dir, config_entries); 
		}
	}

	return 0;
}