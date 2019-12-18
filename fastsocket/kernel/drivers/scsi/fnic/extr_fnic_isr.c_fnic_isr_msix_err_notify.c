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
 size_t FNIC_MSIX_ERR_NOTIFY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  fnic_handle_link_event (struct fnic*) ; 
 int /*<<< orphan*/  fnic_log_q_error (struct fnic*) ; 
 int /*<<< orphan*/  vnic_intr_return_all_credits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fnic_isr_msix_err_notify(int irq, void *data)
{
	struct fnic *fnic = data;

	vnic_intr_return_all_credits(&fnic->intr[FNIC_MSIX_ERR_NOTIFY]);
	fnic_log_q_error(fnic);
	fnic_handle_link_event(fnic);

	return IRQ_HANDLED;
}