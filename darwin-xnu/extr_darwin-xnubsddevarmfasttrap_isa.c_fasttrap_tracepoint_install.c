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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_3__ {int ftt_installed; int /*<<< orphan*/  ftt_pc; scalar_t__ ftt_thumb; } ;
typedef  TYPE_1__ fasttrap_tracepoint_t ;

/* Variables and functions */
 scalar_t__ FASTTRAP_ARM_INSTR ; 
 int /*<<< orphan*/  FASTTRAP_THUMB_INSTR ; 
 scalar_t__ uwrite (int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ) ; 

int
fasttrap_tracepoint_install(proc_t *p, fasttrap_tracepoint_t *tp)
{
	/* The thumb patch is a 2 byte instruction regardless of the size of the original instruction */
	uint32_t instr;
	int size = tp->ftt_thumb ? 2 : 4;

	if (tp->ftt_thumb) {
		*((uint16_t*) &instr) = FASTTRAP_THUMB_INSTR;
	} else {
		instr = FASTTRAP_ARM_INSTR;
	}

	if (uwrite(p, &instr, size, tp->ftt_pc) != 0)
		return (-1);

	tp->ftt_installed = 1;

	return (0);
}