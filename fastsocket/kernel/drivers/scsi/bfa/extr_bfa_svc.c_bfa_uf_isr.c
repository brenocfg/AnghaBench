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
struct bfi_uf_frm_rcvd_s {int dummy; } ;
struct TYPE_2__ {int msg_id; } ;
struct bfi_msg_s {TYPE_1__ mhdr; } ;
struct bfa_s {int dummy; } ;

/* Variables and functions */
#define  BFI_UF_I2H_FRM_RCVD 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int) ; 
 int /*<<< orphan*/  uf_recv (struct bfa_s*,struct bfi_uf_frm_rcvd_s*) ; 

void
bfa_uf_isr(struct bfa_s *bfa, struct bfi_msg_s *msg)
{
	bfa_trc(bfa, msg->mhdr.msg_id);

	switch (msg->mhdr.msg_id) {
	case BFI_UF_I2H_FRM_RCVD:
		uf_recv(bfa, (struct bfi_uf_frm_rcvd_s *) msg);
		break;

	default:
		bfa_trc(bfa, msg->mhdr.msg_id);
		WARN_ON(1);
	}
}