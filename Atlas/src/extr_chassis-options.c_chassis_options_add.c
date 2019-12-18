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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  chassis_options_t ;
typedef  int /*<<< orphan*/  chassis_option_t ;
typedef  int /*<<< orphan*/  GOptionArg ;

/* Variables and functions */
 int /*<<< orphan*/  chassis_option_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * chassis_option_new () ; 
 scalar_t__ chassis_option_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ chassis_options_add_option (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int chassis_options_add(chassis_options_t *opts, 
		const char *long_name,
		gchar short_name,
		gint flags,
		GOptionArg arg,
		gpointer   arg_data,
		const char *description,
		const char *arg_description) {
	chassis_option_t *opt;

	opt = chassis_option_new();
	if (0 != chassis_option_set(opt,
			long_name,
			short_name,
			flags,
			arg,
			arg_data,
			description,
			arg_description) || 
	    0 != chassis_options_add_option(opts, opt)) {
		chassis_option_free(opt);
		return -1;
	} else {
		return 0;
	}
}