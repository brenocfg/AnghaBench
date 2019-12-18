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
typedef  int /*<<< orphan*/  x86_saved_state_t ;

/* Variables and functions */
 int fasttrap_pid_probe32 (int /*<<< orphan*/ *) ; 
 int fasttrap_pid_probe64 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_saved_state64 (int /*<<< orphan*/ *) ; 

int
fasttrap_pid_probe(x86_saved_state_t *regs)
{
        if (is_saved_state64(regs))
		return fasttrap_pid_probe64(regs);

	return fasttrap_pid_probe32(regs);
}