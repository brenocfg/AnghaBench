#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  scalar_t__ uchar_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_4__ {scalar_t__* instr; uintptr_t addr; int /*<<< orphan*/  pid; int /*<<< orphan*/ * dtp; } ;
typedef  TYPE_1__ dtrace_dis_t ;
struct TYPE_5__ {int d86_len; scalar_t__* d86_bytes; int /*<<< orphan*/ * d86_check_func; int /*<<< orphan*/  d86_get_byte; TYPE_1__* d86_data; } ;
typedef  TYPE_2__ dis86_t ;

/* Variables and functions */
 scalar_t__ FASTTRAP_INSTR ; 
 char PR_MODEL_ILP32 ; 
 int /*<<< orphan*/  SIZE32 ; 
 int /*<<< orphan*/  SIZE64 ; 
 int /*<<< orphan*/  dt_getbyte ; 
 scalar_t__ dtrace_disx86 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_instr_size(uchar_t *instr, dtrace_hdl_t *dtp, pid_t pid, uintptr_t addr,
    char dmodel)
{
	dtrace_dis_t data;
	dis86_t x86dis;
	uint_t cpu_mode;

	data.instr = instr;
	data.dtp = dtp;
	data.pid = pid;
	data.addr = addr;

	x86dis.d86_data = &data;
	x86dis.d86_get_byte = dt_getbyte;
	x86dis.d86_check_func = NULL;

	cpu_mode = (dmodel == PR_MODEL_ILP32) ? SIZE32 : SIZE64;

	if (dtrace_disx86(&x86dis, cpu_mode) != 0)
		return (-1);

	/*
	 * If the instruction was a single-byte breakpoint, there may be
	 * another debugger attached to this process. The original instruction
	 * can't be recovered so this must fail.
	 */
	if (x86dis.d86_len == 1 &&
	    (uchar_t)x86dis.d86_bytes[0] == FASTTRAP_INSTR)
		return (-1);

	return (x86dis.d86_len);
}