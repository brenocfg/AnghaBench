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

/* Variables and functions */
 int /*<<< orphan*/  G_OPTION_ARG_NONE ; 
 int /*<<< orphan*/  G_OPTION_ARG_STRING ; 
 int /*<<< orphan*/  chassis_options_add (int /*<<< orphan*/ *,char*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

int chassis_options_set_cmdline_only_options(chassis_options_t *opts,
		int *print_version,
		char **config_file) {

	chassis_options_add(opts,
		"version", 'V', 0, G_OPTION_ARG_NONE, print_version, "Show version", NULL);

	chassis_options_add(opts,
		"defaults-file", 0, 0, G_OPTION_ARG_STRING, config_file, "configuration file", "<file>");

	return 0;
}