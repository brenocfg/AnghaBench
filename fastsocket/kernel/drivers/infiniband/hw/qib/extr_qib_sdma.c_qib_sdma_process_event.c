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
struct TYPE_2__ {scalar_t__ current_state; } ;
struct qib_pportdata {int /*<<< orphan*/  sdma_lock; TYPE_1__ sdma_state; } ;
typedef  enum qib_sdma_events { ____Placeholder_qib_sdma_events } qib_sdma_events ;

/* Variables and functions */
 int /*<<< orphan*/  __qib_sdma_process_event (struct qib_pportdata*,int) ; 
 int /*<<< orphan*/  qib_sdma_descq_freecnt (struct qib_pportdata*) ; 
 scalar_t__ qib_sdma_state_s99_running ; 
 int /*<<< orphan*/  qib_verbs_sdma_desc_avail (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void qib_sdma_process_event(struct qib_pportdata *ppd,
	enum qib_sdma_events event)
{
	unsigned long flags;

	spin_lock_irqsave(&ppd->sdma_lock, flags);

	__qib_sdma_process_event(ppd, event);

	if (ppd->sdma_state.current_state == qib_sdma_state_s99_running)
		qib_verbs_sdma_desc_avail(ppd, qib_sdma_descq_freecnt(ppd));

	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
}