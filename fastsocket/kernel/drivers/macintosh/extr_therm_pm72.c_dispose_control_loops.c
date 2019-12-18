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
 int /*<<< orphan*/  backside_state ; 
 int /*<<< orphan*/ * cpu_state ; 
 int /*<<< orphan*/  dimms_state ; 
 int /*<<< orphan*/  dispose_backside_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispose_cpu_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispose_dimms_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispose_drives_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispose_slots_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drives_state ; 
 int /*<<< orphan*/  slots_state ; 

__attribute__((used)) static void dispose_control_loops(void)
{
	dispose_cpu_state(&cpu_state[0]);
	dispose_cpu_state(&cpu_state[1]);
	dispose_backside_state(&backside_state);
	dispose_drives_state(&drives_state);
	dispose_slots_state(&slots_state);
	dispose_dimms_state(&dimms_state);
}