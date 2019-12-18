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
struct bfa_ioim_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  hcb_qe; TYPE_1__* iosp; int /*<<< orphan*/  reqq; int /*<<< orphan*/  itnim; int /*<<< orphan*/  io_cbfn; } ;
typedef  enum bfa_ioim_event { ____Placeholder_bfa_ioim_event } bfa_ioim_event ;
struct TYPE_2__ {int /*<<< orphan*/  reqq_wait; int /*<<< orphan*/  abort_explicit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
#define  BFA_IOIM_SM_ABORT 134 
#define  BFA_IOIM_SM_CLEANUP 133 
#define  BFA_IOIM_SM_COMP 132 
#define  BFA_IOIM_SM_COMP_GOOD 131 
#define  BFA_IOIM_SM_DONE 130 
#define  BFA_IOIM_SM_HWFAIL 129 
#define  BFA_IOIM_SM_SQRETRY 128 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  __bfa_cb_ioim_abort ; 
 int /*<<< orphan*/  __bfa_cb_ioim_comp ; 
 int /*<<< orphan*/  __bfa_cb_ioim_failed ; 
 int /*<<< orphan*/  __bfa_cb_ioim_good_comp ; 
 int /*<<< orphan*/  bfa_cb_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_maxretry_reached (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_move_to_comp_q (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_send_abort (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_sm_abort ; 
 int /*<<< orphan*/  bfa_ioim_sm_abort_qfull ; 
 int /*<<< orphan*/  bfa_ioim_sm_cleanup ; 
 int /*<<< orphan*/  bfa_ioim_sm_cleanup_qfull ; 
 int /*<<< orphan*/  bfa_ioim_sm_cmnd_retry ; 
 int /*<<< orphan*/  bfa_ioim_sm_hcb ; 
 int /*<<< orphan*/  bfa_ioim_sm_hcb_free ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qwait ; 

__attribute__((used)) static void
bfa_ioim_sm_active(struct bfa_ioim_s *ioim, enum bfa_ioim_event event)
{
	switch (event) {
	case BFA_IOIM_SM_COMP_GOOD:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
			      __bfa_cb_ioim_good_comp, ioim);
		break;

	case BFA_IOIM_SM_COMP:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_comp,
			      ioim);
		break;

	case BFA_IOIM_SM_DONE:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_free);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_comp,
			      ioim);
		break;

	case BFA_IOIM_SM_ABORT:
		ioim->iosp->abort_explicit = BFA_TRUE;
		ioim->io_cbfn = __bfa_cb_ioim_abort;

		if (bfa_ioim_send_abort(ioim))
			bfa_sm_set_state(ioim, bfa_ioim_sm_abort);
		else {
			bfa_sm_set_state(ioim, bfa_ioim_sm_abort_qfull);
			bfa_stats(ioim->itnim, qwait);
			bfa_reqq_wait(ioim->bfa, ioim->reqq,
					  &ioim->iosp->reqq_wait);
		}
		break;

	case BFA_IOIM_SM_CLEANUP:
		ioim->iosp->abort_explicit = BFA_FALSE;
		ioim->io_cbfn = __bfa_cb_ioim_failed;

		if (bfa_ioim_send_abort(ioim))
			bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup);
		else {
			bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup_qfull);
			bfa_stats(ioim->itnim, qwait);
			bfa_reqq_wait(ioim->bfa, ioim->reqq,
					  &ioim->iosp->reqq_wait);
		}
		break;

	case BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		break;

	case BFA_IOIM_SM_SQRETRY:
		if (bfa_ioim_maxretry_reached(ioim)) {
			/* max retry reached, free IO */
			bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_free);
			bfa_ioim_move_to_comp_q(ioim);
			bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
					__bfa_cb_ioim_failed, ioim);
			break;
		}
		/* waiting for IO tag resource free */
		bfa_sm_set_state(ioim, bfa_ioim_sm_cmnd_retry);
		break;

	default:
		bfa_sm_fault(ioim->bfa, event);
	}
}