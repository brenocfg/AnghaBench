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
struct bfa_s {int dummy; } ;
struct bfa_rport_s {int /*<<< orphan*/  rport_tag; } ;
struct bfa_itn_s {void (* isr ) (struct bfa_s*,struct bfi_msg_s*) ;} ;
struct bfa_fcp_mod_s {int dummy; } ;

/* Variables and functions */
 struct bfa_fcp_mod_s* BFA_FCP_MOD (struct bfa_s*) ; 
 struct bfa_itn_s* BFA_ITN_FROM_TAG (struct bfa_fcp_mod_s*,int /*<<< orphan*/ ) ; 

void
bfa_itn_create(struct bfa_s *bfa, struct bfa_rport_s *rport,
		void (*isr)(struct bfa_s *bfa, struct bfi_msg_s *m))
{
	struct bfa_fcp_mod_s *fcp = BFA_FCP_MOD(bfa);
	struct bfa_itn_s *itn;

	itn =  BFA_ITN_FROM_TAG(fcp, rport->rport_tag);
	itn->isr = isr;
}