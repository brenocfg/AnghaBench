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
typedef  int uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct regs {int dummy; } ;
struct arm_saved_state {int /*<<< orphan*/  r; } ;

/* Variables and functions */
 int ARM_SAVED_STATE32_COUNT ; 
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 

uint64_t
dtrace_getreg(struct regs * savearea, uint_t reg)
{
	struct arm_saved_state *regs = (struct arm_saved_state *) savearea;
	if (regs == NULL) {
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	}
	/* beyond register limit? */
	if (reg > ARM_SAVED_STATE32_COUNT - 1) {
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	}

	return (uint64_t) ((unsigned int *) (&(regs->r)))[reg];
}