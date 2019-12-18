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
struct TYPE_5__ {scalar_t__ count; int descrtab_phys; unsigned int hwptr; unsigned int swptr; int /*<<< orphan*/  wait; scalar_t__ mapped; } ;
struct cs4297a_state {TYPE_1__ dma_dac; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  serdma_descr_t ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int EBUSY ; 
 int FRAME_TX_US ; 
 int HZ ; 
 int M_DMA_CURDSCR_ADDR ; 
 int /*<<< orphan*/  R_SER_DMA_CUR_DSCR_ADDR_TX ; 
 int /*<<< orphan*/  R_SER_DMA_DSCR_COUNT_TX ; 
 int /*<<< orphan*/  SS_CSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (unsigned int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_pending (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int drain_dac(struct cs4297a_state *s, int nonblock)
{
	DECLARE_WAITQUEUE(wait, current);
	unsigned long flags;
        unsigned hwptr;
	unsigned tmo;
	int count;

	if (s->dma_dac.mapped)
		return 0;
        if (nonblock)
                return -EBUSY;
	add_wait_queue(&s->dma_dac.wait, &wait);
        while ((count = __raw_readq(SS_CSR(R_SER_DMA_DSCR_COUNT_TX))) ||
               (s->dma_dac.count > 0)) {
                if (!signal_pending(current)) {
                        set_current_state(TASK_INTERRUPTIBLE);
                        /* XXXKW is this calculation working? */
                        tmo = ((count * FRAME_TX_US) * HZ) / 1000000;
                        schedule_timeout(tmo + 1);
                } else {
                        /* XXXKW do I care if there is a signal pending? */
                }
        }
        spin_lock_irqsave(&s->lock, flags);
        /* Reset the bookkeeping */
        hwptr = (int)(((__raw_readq(SS_CSR(R_SER_DMA_CUR_DSCR_ADDR_TX)) & M_DMA_CURDSCR_ADDR) -
                       s->dma_dac.descrtab_phys) / sizeof(serdma_descr_t));
        s->dma_dac.hwptr = s->dma_dac.swptr = hwptr;
        spin_unlock_irqrestore(&s->lock, flags);
	remove_wait_queue(&s->dma_dac.wait, &wait);
	current->state = TASK_RUNNING;
	return 0;
}