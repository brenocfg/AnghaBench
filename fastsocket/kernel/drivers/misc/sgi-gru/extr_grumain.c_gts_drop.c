#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gru_thread_state {scalar_t__ ts_gms; int /*<<< orphan*/  ts_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gru_drop_mmu_notifier (scalar_t__) ; 
 int /*<<< orphan*/  gts_free ; 
 int /*<<< orphan*/  kfree (struct gru_thread_state*) ; 

void gts_drop(struct gru_thread_state *gts)
{
	if (gts && atomic_dec_return(&gts->ts_refcnt) == 0) {
		if (gts->ts_gms)
			gru_drop_mmu_notifier(gts->ts_gms);
		kfree(gts);
		STAT(gts_free);
	}
}