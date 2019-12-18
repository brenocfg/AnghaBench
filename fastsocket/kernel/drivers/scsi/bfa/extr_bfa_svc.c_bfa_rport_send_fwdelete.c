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
struct bfi_rport_delete_req_s {int /*<<< orphan*/  mh; int /*<<< orphan*/  fw_handle; } ;
struct bfa_rport_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  fw_handle; int /*<<< orphan*/  reqq_wait; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_REQQ_RPORT ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_MC_RPORT ; 
 int /*<<< orphan*/  BFI_RPORT_H2I_DELETE_REQ ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_rport_delete_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_boolean_t
bfa_rport_send_fwdelete(struct bfa_rport_s *rp)
{
	struct bfi_rport_delete_req_s *m;

	/*
	 * check for room in queue to send request now
	 */
	m = bfa_reqq_next(rp->bfa, BFA_REQQ_RPORT);
	if (!m) {
		bfa_reqq_wait(rp->bfa, BFA_REQQ_RPORT, &rp->reqq_wait);
		return BFA_FALSE;
	}

	bfi_h2i_set(m->mh, BFI_MC_RPORT, BFI_RPORT_H2I_DELETE_REQ,
			bfa_fn_lpu(rp->bfa));
	m->fw_handle = rp->fw_handle;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(rp->bfa, BFA_REQQ_RPORT, m->mh);
	return BFA_TRUE;
}