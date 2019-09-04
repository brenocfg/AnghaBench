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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * x; int /*<<< orphan*/  sp; int /*<<< orphan*/  lr; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ arm_saved_state64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t 
get_saved_state64_regno(arm_saved_state64_t *regs64, uint32_t regno, int use_xzr)
{
	/* Set PC to register value */
	switch (regno) {
		case 29:
			return regs64->fp;
		case 30:
			return regs64->lr;
		case 31:
			/* xzr */
			if (use_xzr) {
				return 0;
			} else {
				return regs64->sp;
			}
		default:
			return regs64->x[regno];
	}
}