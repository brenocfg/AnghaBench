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
typedef  int /*<<< orphan*/  u8 ;
struct list_head {int /*<<< orphan*/  qe; int /*<<< orphan*/  status; int /*<<< orphan*/  bfa_tag; struct bfa_s* bfa; } ;
struct bfa_s {int dummy; } ;
struct bfa_lps_s {int /*<<< orphan*/  qe; int /*<<< orphan*/  status; int /*<<< orphan*/  bfa_tag; struct bfa_s* bfa; } ;
struct bfa_lps_mod_s {int /*<<< orphan*/  lps_active_q; } ;

/* Variables and functions */
 struct bfa_lps_mod_s* BFA_LPS_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  BFA_LPS_SM_FWRSP ; 
 struct list_head* bfa_q_next (struct list_head*) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct list_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_lps_no_res(struct bfa_lps_s *first_lps, u8 count)
{
	struct bfa_s		*bfa = first_lps->bfa;
	struct bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	struct list_head	*qe, *qe_next;
	struct bfa_lps_s	*lps;

	bfa_trc(bfa, count);

	qe = bfa_q_next(first_lps);

	while (count && qe) {
		qe_next = bfa_q_next(qe);
		lps = (struct bfa_lps_s *)qe;
		bfa_trc(bfa, lps->bfa_tag);
		lps->status = first_lps->status;
		list_del(&lps->qe);
		list_add_tail(&lps->qe, &mod->lps_active_q);
		bfa_sm_send_event(lps, BFA_LPS_SM_FWRSP);
		qe = qe_next;
		count--;
	}
}