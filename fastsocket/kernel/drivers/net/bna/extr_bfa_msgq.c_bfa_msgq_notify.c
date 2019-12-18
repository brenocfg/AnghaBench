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
struct bfa_msgq {int /*<<< orphan*/  rspq; int /*<<< orphan*/  cmdq; int /*<<< orphan*/  init_wc; } ;
typedef  enum bfa_ioc_event { ____Placeholder_bfa_ioc_event } bfa_ioc_event ;

/* Variables and functions */
#define  BFA_IOC_E_DISABLED 130 
#define  BFA_IOC_E_ENABLED 129 
#define  BFA_IOC_E_FAILED 128 
 int /*<<< orphan*/  CMDQ_E_FAIL ; 
 int /*<<< orphan*/  CMDQ_E_START ; 
 int /*<<< orphan*/  CMDQ_E_STOP ; 
 int /*<<< orphan*/  RSPQ_E_FAIL ; 
 int /*<<< orphan*/  RSPQ_E_START ; 
 int /*<<< orphan*/  RSPQ_E_STOP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_msgq_init ; 
 int /*<<< orphan*/  bfa_wc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_msgq*) ; 
 int /*<<< orphan*/  bfa_wc_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_wc_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_msgq_notify(void *cbarg, enum bfa_ioc_event event)
{
	struct bfa_msgq *msgq = (struct bfa_msgq *)cbarg;

	switch (event) {
	case BFA_IOC_E_ENABLED:
		bfa_wc_init(&msgq->init_wc, bfa_msgq_init, msgq);
		bfa_wc_up(&msgq->init_wc);
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_START);
		bfa_wc_up(&msgq->init_wc);
		bfa_fsm_send_event(&msgq->rspq, RSPQ_E_START);
		bfa_wc_wait(&msgq->init_wc);
		break;

	case BFA_IOC_E_DISABLED:
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_STOP);
		bfa_fsm_send_event(&msgq->rspq, RSPQ_E_STOP);
		break;

	case BFA_IOC_E_FAILED:
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_FAIL);
		bfa_fsm_send_event(&msgq->rspq, RSPQ_E_FAIL);
		break;

	default:
		break;
	}
}