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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_3__ {scalar_t__ ftt_installed; int /*<<< orphan*/  ftt_pc; int /*<<< orphan*/  ftt_instr; scalar_t__ ftt_thumb; } ;
typedef  TYPE_1__ fasttrap_tracepoint_t ;

/* Variables and functions */
 scalar_t__ FASTTRAP_ARM_INSTR ; 
 scalar_t__ FASTTRAP_THUMB_INSTR ; 
 scalar_t__ uread (int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ uwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
fasttrap_tracepoint_remove(proc_t *p, fasttrap_tracepoint_t *tp)
{
	/* The thumb patch is a 2 byte instruction regardless of the size of the original instruction */
	uint32_t instr;
	int size = tp->ftt_thumb ? 2 : 4;

	/*
	 * Distinguish between read or write failures and a changed
	 * instruction.
	 */
	if (uread(p, &instr, size, tp->ftt_pc) != 0)
		goto end;
	if (tp->ftt_thumb) {
		if (*((uint16_t*) &instr) != FASTTRAP_THUMB_INSTR)
			goto end;
	} else {
		if (instr != FASTTRAP_ARM_INSTR)
			goto end;
	}
	if (uwrite(p, &tp->ftt_instr, size, tp->ftt_pc) != 0)
		return (-1);

end:
	tp->ftt_installed = 0;

	return (0);
}