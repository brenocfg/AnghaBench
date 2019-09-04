#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* queue_entry_t ;
typedef  TYPE_2__* pv_hashed_entry_t ;
struct TYPE_11__ {int /*<<< orphan*/  options; } ;
struct TYPE_9__ {void* next; } ;
struct TYPE_10__ {TYPE_1__ qlink; } ;

/* Variables and functions */
 TYPE_2__* PV_HASHED_ENTRY_NULL ; 
 int /*<<< orphan*/  PV_HASHED_FREE_LIST (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  PV_HASHED_KERN_FREE_LIST (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  TH_OPT_VMPRIV ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* current_thread () ; 
 int /*<<< orphan*/  mapping_replenish_event ; 
 scalar_t__ mappingrecurse ; 
 int pmap_kernel_reserve_replenish_stat ; 
 int /*<<< orphan*/  pmap_mapping_thread_wakeups ; 
 scalar_t__ pmap_pv_throttled_waiters ; 
 int /*<<< orphan*/  pmap_user_pv_throttle_event ; 
 int pmap_user_reserve_replenish_stat ; 
 unsigned int pv_hashed_alloc_chunk ; 
 scalar_t__ pv_hashed_free_count ; 
 unsigned int pv_hashed_kern_alloc_chunk ; 
 scalar_t__ pv_hashed_kern_free_count ; 
 scalar_t__ pv_hashed_kern_low_water_mark ; 
 int /*<<< orphan*/  pv_hashed_list_zone ; 
 scalar_t__ pv_hashed_low_water_mark ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ *) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

__attribute__((noreturn))
void
mapping_replenish(void)
{
	pv_hashed_entry_t	pvh_e;
	pv_hashed_entry_t	pvh_eh;
	pv_hashed_entry_t	pvh_et;
	int			pv_cnt;
	unsigned             	i;

	/* We qualify for VM privileges...*/
	current_thread()->options |= TH_OPT_VMPRIV;

	for (;;) {

		while (pv_hashed_kern_free_count < pv_hashed_kern_low_water_mark) {
			pv_cnt = 0;
			pvh_eh = pvh_et = PV_HASHED_ENTRY_NULL;

			for (i = 0; i < pv_hashed_kern_alloc_chunk; i++) {
				pvh_e = (pv_hashed_entry_t) zalloc(pv_hashed_list_zone);
				pvh_e->qlink.next = (queue_entry_t)pvh_eh;
				pvh_eh = pvh_e;

				if (pvh_et == PV_HASHED_ENTRY_NULL)
					pvh_et = pvh_e;
				pv_cnt++;
			}
			pmap_kernel_reserve_replenish_stat += pv_cnt;
			PV_HASHED_KERN_FREE_LIST(pvh_eh, pvh_et, pv_cnt);
		}

		pv_cnt = 0;
		pvh_eh = pvh_et = PV_HASHED_ENTRY_NULL;

		if (pv_hashed_free_count < pv_hashed_low_water_mark) {
			for (i = 0; i < pv_hashed_alloc_chunk; i++) {
				pvh_e = (pv_hashed_entry_t) zalloc(pv_hashed_list_zone);

				pvh_e->qlink.next = (queue_entry_t)pvh_eh;
				pvh_eh = pvh_e;

				if (pvh_et == PV_HASHED_ENTRY_NULL)
					pvh_et = pvh_e;
				pv_cnt++;
			}
			pmap_user_reserve_replenish_stat += pv_cnt;
			PV_HASHED_FREE_LIST(pvh_eh, pvh_et, pv_cnt);
		}
/* Wake threads throttled while the kernel reserve was being replenished.
 */
		if (pmap_pv_throttled_waiters) {
			pmap_pv_throttled_waiters = 0;
			thread_wakeup(&pmap_user_pv_throttle_event);
		}
		/* Check if the kernel pool has been depleted since the
		 * first pass, to reduce refill latency.
		 */
		if (pv_hashed_kern_free_count < pv_hashed_kern_low_water_mark)
			continue;
		/* Block sans continuation to avoid yielding kernel stack */
		assert_wait(&mapping_replenish_event, THREAD_UNINT);
		mappingrecurse = 0;
		thread_block(THREAD_CONTINUE_NULL);
		pmap_mapping_thread_wakeups++;
	}
}