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
struct TYPE_2__ {int /*<<< orphan*/  comp; int /*<<< orphan*/  kref; } ;
struct qib_pportdata {int /*<<< orphan*/  sdma_sw_clean_up_task; int /*<<< orphan*/  sdma_activelist; scalar_t__ sdma_descq_added; scalar_t__ sdma_descq_removed; scalar_t__ sdma_descq_head; scalar_t__ sdma_generation; TYPE_1__ sdma_state; int /*<<< orphan*/  sdma_lock; struct qib_devdata* dd; } ;
struct qib_devdata {int (* f_init_sdma_regs ) (struct qib_pportdata*) ;int /*<<< orphan*/  (* f_sdma_init_early ) (struct qib_pportdata*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int alloc_sdma (struct qib_pportdata*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_sdma_event_e10_go_hw_start ; 
 int /*<<< orphan*/  qib_sdma_process_event (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_sdma_state_s00_hw_down ; 
 int /*<<< orphan*/  qib_teardown_sdma (struct qib_pportdata*) ; 
 int /*<<< orphan*/  sdma_set_state (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_sw_clean_up_task ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*) ; 
 int stub2 (struct qib_pportdata*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int qib_setup_sdma(struct qib_pportdata *ppd)
{
	struct qib_devdata *dd = ppd->dd;
	unsigned long flags;
	int ret = 0;

	ret = alloc_sdma(ppd);
	if (ret)
		goto bail;

	/* set consistent sdma state */
	ppd->dd->f_sdma_init_early(ppd);
	spin_lock_irqsave(&ppd->sdma_lock, flags);
	sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
	spin_unlock_irqrestore(&ppd->sdma_lock, flags);

	/* set up reference counting */
	kref_init(&ppd->sdma_state.kref);
	init_completion(&ppd->sdma_state.comp);

	ppd->sdma_generation = 0;
	ppd->sdma_descq_head = 0;
	ppd->sdma_descq_removed = 0;
	ppd->sdma_descq_added = 0;

	INIT_LIST_HEAD(&ppd->sdma_activelist);

	tasklet_init(&ppd->sdma_sw_clean_up_task, sdma_sw_clean_up_task,
		(unsigned long)ppd);

	ret = dd->f_init_sdma_regs(ppd);
	if (ret)
		goto bail_alloc;

	qib_sdma_process_event(ppd, qib_sdma_event_e10_go_hw_start);

	return 0;

bail_alloc:
	qib_teardown_sdma(ppd);
bail:
	return ret;
}