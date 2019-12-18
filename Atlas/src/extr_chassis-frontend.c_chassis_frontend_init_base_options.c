#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  chassis_options_t ;
typedef  int /*<<< orphan*/  GOptionEntry ;
typedef  int /*<<< orphan*/  GOptionContext ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  chassis_options_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * chassis_options_new () ; 
 int /*<<< orphan*/  chassis_options_set_cmdline_only_options (int /*<<< orphan*/ *,int*,char**) ; 
 int /*<<< orphan*/ * chassis_options_to_g_option_entries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_option_context_add_main_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ g_option_context_parse (int /*<<< orphan*/ *,int*,char***,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_option_context_set_help_enabled (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  g_option_context_set_ignore_unknown_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int chassis_frontend_init_base_options(GOptionContext *option_ctx,
		int *argc_p, char ***argv_p,
		int *print_version,
		char **config_file,
		GError **gerr) {
	chassis_options_t *opts;
	GOptionEntry *base_main_entries;
	int ret = 0;

	opts = chassis_options_new();
	chassis_options_set_cmdline_only_options(opts, print_version, config_file);
	base_main_entries = chassis_options_to_g_option_entries(opts);

	g_option_context_add_main_entries(option_ctx, base_main_entries, NULL);
	g_option_context_set_help_enabled(option_ctx, FALSE);
	g_option_context_set_ignore_unknown_options(option_ctx, TRUE);

	if (FALSE == g_option_context_parse(option_ctx, argc_p, argv_p, gerr)) {
		ret = -1;
	}

	/* do not use chassis_options_free_g_options... here, we need to hang on to the data until the end of the program! */
	g_free(base_main_entries);
	chassis_options_free(opts);

	return ret;
}