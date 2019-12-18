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
typedef  int /*<<< orphan*/  thread_t ;
struct x86_fx_thread_state {scalar_t__ fp_valid; } ;
typedef  TYPE_1__* pcb_t ;
struct TYPE_3__ {struct x86_fx_thread_state* ifps; } ;

/* Variables and functions */
 int CR0_TS ; 
 TYPE_1__* THREAD_TO_PCB (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fpu_store_registers (struct x86_fx_thread_state*,int /*<<< orphan*/ ) ; 
 int get_cr0 () ; 
 int /*<<< orphan*/  thread_is_64bit_addr (int /*<<< orphan*/ ) ; 

void
fp_save(
	thread_t	thr_act)
{
	pcb_t pcb = THREAD_TO_PCB(thr_act);
	struct x86_fx_thread_state *ifps = pcb->ifps;

	assert(ifps != 0);
	if (ifps != 0 && !ifps->fp_valid) {
		assert((get_cr0() & CR0_TS) == 0);
		/* registers are in FPU */
		ifps->fp_valid = TRUE;
		fpu_store_registers(ifps, thread_is_64bit_addr(thr_act));
	}
}