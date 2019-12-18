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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {void* arg_description; void* description; int /*<<< orphan*/  arg_data; int /*<<< orphan*/  arg; int /*<<< orphan*/  flags; int /*<<< orphan*/  short_name; void* long_name; } ;
typedef  TYPE_1__ chassis_option_t ;
typedef  int /*<<< orphan*/  GOptionArg ;

/* Variables and functions */
 void* g_strdup (char const*) ; 

int chassis_option_set(chassis_option_t *opt, 
		const char *long_name,
		gchar short_name,
		gint flags,
		GOptionArg arg,
		gpointer   arg_data,
		const char *description,
		const char *arg_description) {
	opt->long_name       = g_strdup(long_name);
	opt->short_name      = short_name;
	opt->flags           = flags;
	opt->arg             = arg;
	opt->arg_data        = arg_data;
	opt->description     = g_strdup(description);
	opt->arg_description = g_strdup(arg_description);

	return 0;
}