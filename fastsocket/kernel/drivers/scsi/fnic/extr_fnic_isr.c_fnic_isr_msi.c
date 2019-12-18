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
struct fnic {int /*<<< orphan*/ * intr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ fnic_rq_cmpl_handler (struct fnic*,int) ; 
 scalar_t__ fnic_wq_cmpl_handler (struct fnic*,int) ; 
 scalar_t__ fnic_wq_copy_cmpl_handler (struct fnic*,int) ; 
 int /*<<< orphan*/  vnic_intr_return_credits (int /*<<< orphan*/ *,unsigned long,int,int) ; 

__attribute__((used)) static irqreturn_t fnic_isr_msi(int irq, void *data)
{
	struct fnic *fnic = data;
	unsigned long work_done = 0;

	work_done += fnic_wq_copy_cmpl_handler(fnic, -1);
	work_done += fnic_wq_cmpl_handler(fnic, -1);
	work_done += fnic_rq_cmpl_handler(fnic, -1);

	vnic_intr_return_credits(&fnic->intr[0],
				 work_done,
				 1 /* unmask intr */,
				 1 /* reset intr timer */);

	return IRQ_HANDLED;
}