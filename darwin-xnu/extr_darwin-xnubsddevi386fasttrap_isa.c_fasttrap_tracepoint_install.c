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
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_3__ {int ftt_installed; int /*<<< orphan*/  ftt_pc; } ;
typedef  TYPE_1__ fasttrap_tracepoint_t ;
typedef  int /*<<< orphan*/  fasttrap_instr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FASTTRAP_INSTR ; 
 scalar_t__ uwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
fasttrap_tracepoint_install(proc_t *p, fasttrap_tracepoint_t *tp)
{
	fasttrap_instr_t instr = FASTTRAP_INSTR;

	if (uwrite(p, &instr, 1, tp->ftt_pc) != 0)
		return (-1);

	tp->ftt_installed = 1;

	return (0);
}