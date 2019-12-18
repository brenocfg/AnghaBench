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
#define  BFA_IOIM_SM_ABORT 131 
#define  BFA_IOIM_SM_CLEANUP 130 
#define  BFA_IOIM_SM_FREE 129 
#define  BFA_IOIM_SM_HWFAIL 128 
 int /*<<< orphan*/  __bfa_cb_ioim_abort ; 
 int /*<<< orphan*/  __bfa_cb_ioim_failed ; 
 int /*<<< orphan*/  bfa_cb_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_move_to_comp_q (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_send_abort (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_send_ioreq (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_sm_active ; 
 int /*<<< orphan*/  bfa_ioim_sm_cleanup ; 
 int /*<<< orphan*/  bfa_ioim_sm_cleanup_qfull ; 
 int /*<<< orphan*/  bfa_ioim_sm_hcb ; 
 int /*<<< orphan*/  bfa_ioim_sm_hcb_free ; 
 int /*<<< orphan*/  bfa_ioim_sm_qfull ; 
 int /*<<< orphan*/  bfa_ioim_update_iotag (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qwait ; 

__attribute__((used)) static void
bfa_ioim_sm_cmnd_retry(struct bfa_ioim_s *ioim, enum bfa_ioim_event event)
{
	switch (event) {
	case BFA_IOIM_SM_FREE:
		/* abts and rrq done. Now retry the IO with new tag */
		bfa_ioim_update_iotag(ioim);
		if (!bfa_ioim_send_ioreq(ioim)) {
			bfa_sm_set_state(ioim, bfa_ioim_sm_qfull);
			break;
		}
		bfa_sm_set_state(ioim, bfa_ioim_sm_active);
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
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
			 __bfa_cb_ioim_failed, ioim);
		break;

	case BFA_IOIM_SM_ABORT:
		/* in this state IO abort is done.
		 * Waiting for IO tag resource free.
		 */
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_free);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_abort,
			      ioim);
		break;

	default:
		bfa_sm_fault(ioim->bfa, event);
	}
}