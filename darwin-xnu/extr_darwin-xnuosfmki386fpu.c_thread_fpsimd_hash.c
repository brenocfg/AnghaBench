#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct x86_fx_thread_state {scalar_t__ fp_valid; int /*<<< orphan*/ ** fx_XMM_reg; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {struct x86_fx_thread_state* ifps; } ;

/* Variables and functions */
 uintptr_t CR0_TS ; 
 scalar_t__ FALSE ; 
 TYPE_1__* THREAD_TO_PCB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_ts () ; 
 int /*<<< orphan*/  fp_save (int /*<<< orphan*/ ) ; 
 scalar_t__ fpsimd_fault_popc ; 
 int /*<<< orphan*/  fpsimd_pop (uintptr_t,int) ; 
 uintptr_t get_cr0 () ; 
 scalar_t__ ml_set_interrupts_enabled (scalar_t__) ; 
 int /*<<< orphan*/  set_cr0 (uintptr_t) ; 

uint32_t thread_fpsimd_hash(thread_t ft) {
	if (fpsimd_fault_popc == 0)
		return 0;

	uint32_t prv = 0;
	boolean_t istate = ml_set_interrupts_enabled(FALSE);
	struct x86_fx_thread_state *pifps = THREAD_TO_PCB(ft)->ifps;

	if (pifps) {
		if (pifps->fp_valid) {
			prv = fpsimd_pop((uintptr_t) &pifps->fx_XMM_reg[0][0],
			    sizeof(pifps->fx_XMM_reg));
		} else {
			uintptr_t cr0 = get_cr0();
			clear_ts();
			fp_save(ft);
			prv = fpsimd_pop((uintptr_t) &pifps->fx_XMM_reg[0][0],
			    sizeof(pifps->fx_XMM_reg));
			pifps->fp_valid = FALSE;
			if (cr0 & CR0_TS) {
				set_cr0(cr0);
			}
		}
	}
	ml_set_interrupts_enabled(istate);
	return prv;
}