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
typedef  scalar_t__ u64 ;
struct qib_pportdata {int dummy; } ;
struct qib_devdata {int flags; scalar_t__ traffic_wds; int /*<<< orphan*/  stats_timer; int /*<<< orphan*/  eep_st_lock; int /*<<< orphan*/  active_time; scalar_t__ diag_client; struct qib_pportdata* pport; } ;

/* Variables and functions */
 int ACTIVITY_TIMER ; 
 int HZ ; 
 int QIB_INITTED ; 
 scalar_t__ QIB_TRAFFIC_ACTIVE_THRESHOLD ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cr_wordrcv ; 
 int /*<<< orphan*/  cr_wordsend ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ qib_portcntr_7220 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qib_get_7220_faststats(unsigned long opaque)
{
	struct qib_devdata *dd = (struct qib_devdata *) opaque;
	struct qib_pportdata *ppd = dd->pport;
	unsigned long flags;
	u64 traffic_wds;

	/*
	 * don't access the chip while running diags, or memory diags can
	 * fail
	 */
	if (!(dd->flags & QIB_INITTED) || dd->diag_client)
		/* but re-arm the timer, for diags case; won't hurt other */
		goto done;

	/*
	 * We now try to maintain an activity timer, based on traffic
	 * exceeding a threshold, so we need to check the word-counts
	 * even if they are 64-bit.
	 */
	traffic_wds = qib_portcntr_7220(ppd, cr_wordsend) +
		qib_portcntr_7220(ppd, cr_wordrcv);
	spin_lock_irqsave(&dd->eep_st_lock, flags);
	traffic_wds -= dd->traffic_wds;
	dd->traffic_wds += traffic_wds;
	if (traffic_wds  >= QIB_TRAFFIC_ACTIVE_THRESHOLD)
		atomic_add(5, &dd->active_time); /* S/B #define */
	spin_unlock_irqrestore(&dd->eep_st_lock, flags);
done:
	mod_timer(&dd->stats_timer, jiffies + HZ * ACTIVITY_TIMER);
}