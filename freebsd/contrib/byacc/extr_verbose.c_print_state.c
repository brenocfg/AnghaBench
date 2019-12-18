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
 scalar_t__* RRconflicts ; 
 scalar_t__* SRconflicts ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_actions (int) ; 
 int /*<<< orphan*/  print_conflicts (int) ; 
 int /*<<< orphan*/  print_core (int) ; 
 int /*<<< orphan*/  print_nulls (int) ; 
 int /*<<< orphan*/  verbose_file ; 

__attribute__((used)) static void
print_state(int state)
{
    if (state)
	fprintf(verbose_file, "\n\n");
    if (SRconflicts[state] || RRconflicts[state])
	print_conflicts(state);
    fprintf(verbose_file, "state %d\n", state);
    print_core(state);
    print_nulls(state);
    print_actions(state);
}