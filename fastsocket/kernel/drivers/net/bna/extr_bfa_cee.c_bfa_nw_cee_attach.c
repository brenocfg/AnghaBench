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
struct bfa_ioc {int dummy; } ;
struct bfa_cee {int /*<<< orphan*/  ioc_notify; struct bfa_ioc* ioc; void* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_CEE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bfa_cee_isr ; 
 int /*<<< orphan*/  bfa_cee_notify ; 
 int /*<<< orphan*/  bfa_ioc_notify_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_cee*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_mbox_regisr (struct bfa_ioc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_cee*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_notify_register (struct bfa_ioc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_q_qe_init (int /*<<< orphan*/ *) ; 

void
bfa_nw_cee_attach(struct bfa_cee *cee, struct bfa_ioc *ioc,
		void *dev)
{
	BUG_ON(!(cee != NULL));
	cee->dev = dev;
	cee->ioc = ioc;

	bfa_nw_ioc_mbox_regisr(cee->ioc, BFI_MC_CEE, bfa_cee_isr, cee);
	bfa_q_qe_init(&cee->ioc_notify);
	bfa_ioc_notify_init(&cee->ioc_notify, bfa_cee_notify, cee);
	bfa_nw_ioc_notify_register(cee->ioc, &cee->ioc_notify);
}