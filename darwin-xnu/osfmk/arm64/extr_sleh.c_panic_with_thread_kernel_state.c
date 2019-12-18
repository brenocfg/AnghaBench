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
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_3__ {int /*<<< orphan*/  far; int /*<<< orphan*/  esr; int /*<<< orphan*/  cpsr; int /*<<< orphan*/  pc; int /*<<< orphan*/  sp; int /*<<< orphan*/  lr; int /*<<< orphan*/  fp; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ arm_saved_state64_t ;

/* Variables and functions */
 scalar_t__ is_saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic_plain (char*,char const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* saved_state64 (int /*<<< orphan*/ *) ; 

void
panic_with_thread_kernel_state(const char *msg, arm_saved_state_t *ss)
{
	boolean_t ss_valid;

	ss_valid = is_saved_state64(ss);
	arm_saved_state64_t *state = saved_state64(ss);

	panic_plain("%s (saved state: %p%s)\n"
		"\t  x0: 0x%016llx  x1:  0x%016llx  x2:  0x%016llx  x3:  0x%016llx\n"
		"\t  x4: 0x%016llx  x5:  0x%016llx  x6:  0x%016llx  x7:  0x%016llx\n"
		"\t  x8: 0x%016llx  x9:  0x%016llx  x10: 0x%016llx  x11: 0x%016llx\n"
		"\t  x12: 0x%016llx x13: 0x%016llx  x14: 0x%016llx  x15: 0x%016llx\n"
		"\t  x16: 0x%016llx x17: 0x%016llx  x18: 0x%016llx  x19: 0x%016llx\n"
		"\t  x20: 0x%016llx x21: 0x%016llx  x22: 0x%016llx  x23: 0x%016llx\n"
		"\t  x24: 0x%016llx x25: 0x%016llx  x26: 0x%016llx  x27: 0x%016llx\n"
		"\t  x28: 0x%016llx fp:  0x%016llx  lr:  0x%016llx  sp:  0x%016llx\n"
		"\t  pc:  0x%016llx cpsr: 0x%08x         esr: 0x%08x          far: 0x%016llx\n",
			msg, ss, (ss_valid ? "" : " INVALID"),
			state->x[0], state->x[1], state->x[2], state->x[3],
			state->x[4], state->x[5], state->x[6], state->x[7],
			state->x[8], state->x[9], state->x[10], state->x[11],
			state->x[12], state->x[13], state->x[14], state->x[15],
			state->x[16], state->x[17], state->x[18], state->x[19],
			state->x[20], state->x[21], state->x[22], state->x[23],
			state->x[24], state->x[25], state->x[26], state->x[27],
			state->x[28], state->fp, state->lr, state->sp,
			state->pc, state->cpsr, state->esr, state->far);
}