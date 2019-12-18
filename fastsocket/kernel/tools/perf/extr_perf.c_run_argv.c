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

/* Variables and functions */
 int /*<<< orphan*/  execv_dashed_external (char const**) ; 
 int /*<<< orphan*/  handle_alias (int*,char const***) ; 
 int /*<<< orphan*/  handle_internal_command (int,char const**) ; 

__attribute__((used)) static int run_argv(int *argcp, const char ***argv)
{
	int done_alias = 0;

	while (1) {
		/* See if it's an internal command */
		handle_internal_command(*argcp, *argv);

		/* .. then try the external ones */
		execv_dashed_external(*argv);

		/* It could be an alias -- this works around the insanity
		 * of overriding "perf log" with "perf show" by having
		 * alias.log = show
		 */
		if (done_alias || !handle_alias(argcp, argv))
			break;
		done_alias = 1;
	}

	return done_alias;
}