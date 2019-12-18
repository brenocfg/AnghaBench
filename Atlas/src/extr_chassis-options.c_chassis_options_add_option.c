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
struct TYPE_3__ {int /*<<< orphan*/  options; } ;
typedef  TYPE_1__ chassis_options_t ;
typedef  int /*<<< orphan*/  chassis_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int chassis_options_add_option(chassis_options_t *opts, 
		chassis_option_t *opt) {

	opts->options = g_list_append(opts->options, opt);

	return 0;
}