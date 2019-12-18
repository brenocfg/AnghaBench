#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ftiq_instr; int /*<<< orphan*/  ftiq_pc; int /*<<< orphan*/  ftiq_pid; } ;
typedef  TYPE_2__ fasttrap_instr_query_t ;
struct TYPE_7__ {int* instr; int /*<<< orphan*/  addr; TYPE_1__* dtp; int /*<<< orphan*/  pid; } ;
typedef  TYPE_3__ dtrace_dis_t ;
struct TYPE_5__ {int /*<<< orphan*/  dt_ftfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FASTTRAPIOC_GETINSTR ; 
 int FASTTRAP_INSTR ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int
dt_getbyte(void *data)
{
	dtrace_dis_t	*dis = data;
	int ret = *dis->instr;

	if (ret == FASTTRAP_INSTR) {
		fasttrap_instr_query_t instr;

		instr.ftiq_pid = dis->pid;
		instr.ftiq_pc = dis->addr;

		/*
		 * If we hit a byte that looks like the fasttrap provider's
		 * trap instruction (which doubles as the breakpoint
		 * instruction for debuggers) we need to query the kernel
		 * for the real value. This may just be part of an immediate
		 * value so there's no need to return an error if the
		 * kernel doesn't know about this address.
		 */
		if (ioctl(dis->dtp->dt_ftfd, FASTTRAPIOC_GETINSTR, &instr) == 0)
			ret = instr.ftiq_instr;
	}

	dis->addr++;
	dis->instr++;

	return (ret);
}