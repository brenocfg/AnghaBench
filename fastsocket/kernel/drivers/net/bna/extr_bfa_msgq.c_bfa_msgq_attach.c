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
struct bfa_msgq {int /*<<< orphan*/  ioc_notify; struct bfa_ioc* ioc; int /*<<< orphan*/  rspq; int /*<<< orphan*/  cmdq; } ;
struct bfa_ioc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_MSGQ ; 
 int /*<<< orphan*/  bfa_ioc_notify_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_msgq*) ; 
 int /*<<< orphan*/  bfa_msgq_cmdq_attach (int /*<<< orphan*/ *,struct bfa_msgq*) ; 
 int /*<<< orphan*/  bfa_msgq_isr ; 
 int /*<<< orphan*/  bfa_msgq_notify ; 
 int /*<<< orphan*/  bfa_msgq_rspq_attach (int /*<<< orphan*/ *,struct bfa_msgq*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_mbox_regisr (struct bfa_ioc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_msgq*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_notify_register (struct bfa_ioc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_q_qe_init (int /*<<< orphan*/ *) ; 

void
bfa_msgq_attach(struct bfa_msgq *msgq, struct bfa_ioc *ioc)
{
	msgq->ioc    = ioc;

	bfa_msgq_cmdq_attach(&msgq->cmdq, msgq);
	bfa_msgq_rspq_attach(&msgq->rspq, msgq);

	bfa_nw_ioc_mbox_regisr(msgq->ioc, BFI_MC_MSGQ, bfa_msgq_isr, msgq);
	bfa_q_qe_init(&msgq->ioc_notify);
	bfa_ioc_notify_init(&msgq->ioc_notify, bfa_msgq_notify, msgq);
	bfa_nw_ioc_notify_register(msgq->ioc, &msgq->ioc_notify);
}