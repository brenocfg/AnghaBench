#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfi_diag_ts_req_s {int /*<<< orphan*/  mh; int /*<<< orphan*/  temp; } ;
struct TYPE_4__ {scalar_t__ msg; } ;
struct TYPE_3__ {TYPE_2__ mbcmd; } ;
struct bfa_diag_s {TYPE_1__ tsensor; int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_DIAG_H2I_TEMPSENSOR ; 
 int /*<<< orphan*/  BFI_MC_DIAG ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_diag_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
diag_tempsensor_send(struct bfa_diag_s *diag)
{
	struct bfi_diag_ts_req_s *msg;

	msg = (struct bfi_diag_ts_req_s *)diag->tsensor.mbcmd.msg;
	bfa_trc(diag, msg->temp);
	/* build host command */
	bfi_h2i_set(msg->mh, BFI_MC_DIAG, BFI_DIAG_H2I_TEMPSENSOR,
		bfa_ioc_portid(diag->ioc));
	/* send mbox cmd */
	bfa_ioc_mbox_queue(diag->ioc, &diag->tsensor.mbcmd);
}