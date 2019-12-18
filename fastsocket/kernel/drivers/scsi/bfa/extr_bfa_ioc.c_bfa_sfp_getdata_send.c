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
struct bfi_sfp_req_s {int /*<<< orphan*/  mh; int /*<<< orphan*/  memtype; } ;
struct TYPE_2__ {scalar_t__ msg; } ;
struct bfa_sfp_s {TYPE_1__ mbcmd; int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_SFP ; 
 int /*<<< orphan*/  BFI_SFP_H2I_SHOW ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_sfp_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_sfp_getdata_send(struct bfa_sfp_s *sfp)
{
	struct bfi_sfp_req_s *req = (struct bfi_sfp_req_s *)sfp->mbcmd.msg;

	bfa_trc(sfp, req->memtype);

	/* build host command */
	bfi_h2i_set(req->mh, BFI_MC_SFP, BFI_SFP_H2I_SHOW,
			bfa_ioc_portid(sfp->ioc));

	/* send mbox cmd */
	bfa_ioc_mbox_queue(sfp->ioc, &sfp->mbcmd);
}