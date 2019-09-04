#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * mtc_snaps; int /*<<< orphan*/ * mtc_counts; } ;
struct TYPE_6__ {TYPE_1__ cpu_monotonic; } ;
typedef  TYPE_2__ cpu_data_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;

/* Variables and functions */
 unsigned int CORE_NCTRS ; 
 int /*<<< orphan*/  DBG_MONOTONIC ; 
 int /*<<< orphan*/  DBG_MT_DEBUG ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KDBG_EVENTID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KDBG_RELEASE (int /*<<< orphan*/ ,unsigned int,int) ; 
 unsigned int MT_CORE_NFIXED ; 
 int PMSR_OVF (unsigned int) ; 
 int PSR64_IS_USER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_fetch_add_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_set_enabled () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_saved_state_cpsr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_user_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/ * mt_core_reset_values ; 
 int /*<<< orphan*/  mt_core_set_snap (unsigned int,int /*<<< orphan*/ ) ; 
 int mt_cpu_update_count (TYPE_2__*,unsigned int) ; 
 unsigned int mt_microstackshot_ctr ; 
 int /*<<< orphan*/  mt_microstackshot_ctx ; 
 int /*<<< orphan*/  mt_microstackshot_pmi_handler (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mt_microstackshots ; 
 int /*<<< orphan*/  mt_pmis ; 

__attribute__((used)) static void
mt_cpu_pmi(cpu_data_t *cpu, uint64_t pmsr)
{
	assert(cpu != NULL);
	assert(ml_get_interrupts_enabled() == FALSE);

	(void)atomic_fetch_add_explicit(&mt_pmis, 1, memory_order_relaxed);

	/*
	 * monotonic handles any fixed counter PMIs.
	 */
	for (unsigned int i = 0; i < MT_CORE_NFIXED; i++) {
		if ((pmsr & PMSR_OVF(i)) == 0) {
			continue;
		}

		uint64_t count = mt_cpu_update_count(cpu, i);
		cpu->cpu_monotonic.mtc_counts[i] += count;
		mt_core_set_snap(i, mt_core_reset_values[i]);
		cpu->cpu_monotonic.mtc_snaps[i] = mt_core_reset_values[i];

		if (mt_microstackshots && mt_microstackshot_ctr == i) {
			bool user_mode = false;
			arm_saved_state_t *state = get_user_regs(current_thread());
			if (state) {
				user_mode = PSR64_IS_USER(get_saved_state_cpsr(state));
			}
			KDBG_RELEASE(KDBG_EVENTID(DBG_MONOTONIC, DBG_MT_DEBUG, 1),
					mt_microstackshot_ctr, user_mode);
			mt_microstackshot_pmi_handler(user_mode, mt_microstackshot_ctx);
		}
	}

	/*
	 * KPC handles the configurable counter PMIs.
	 */
	for (unsigned int i = MT_CORE_NFIXED; i < CORE_NCTRS; i++) {
		if (pmsr & PMSR_OVF(i)) {
			extern void kpc_pmi_handler(unsigned int ctr);
			kpc_pmi_handler(i);
		}
	}

	core_set_enabled();
}