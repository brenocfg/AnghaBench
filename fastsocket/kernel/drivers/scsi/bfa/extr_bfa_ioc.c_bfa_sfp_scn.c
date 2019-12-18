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
struct bfi_sfp_scn_s {int event; } ;
struct bfi_mbmsg_s {int dummy; } ;
struct bfa_sfp_s {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  data_valid; } ;

/* Variables and functions */
#define  BFA_SFP_SCN_FAILED 133 
#define  BFA_SFP_SCN_INSERTED 132 
#define  BFA_SFP_SCN_POM 131 
#define  BFA_SFP_SCN_REMOVED 130 
#define  BFA_SFP_SCN_UNSUPPORT 129 
#define  BFA_SFP_SCN_VALID 128 
 int /*<<< orphan*/  BFA_SFP_STATE_FAILED ; 
 int /*<<< orphan*/  BFA_SFP_STATE_INSERTED ; 
 int /*<<< orphan*/  BFA_SFP_STATE_REMOVED ; 
 int /*<<< orphan*/  BFA_SFP_STATE_UNSUPPORT ; 
 int /*<<< orphan*/  BFA_SFP_STATE_VALID ; 
 int /*<<< orphan*/  BFI_SFP_MEM_ALL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_sfp_getdata (struct bfa_sfp_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sfp_scn_aen_post (struct bfa_sfp_s*,struct bfi_sfp_scn_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_sfp_s*,int) ; 

__attribute__((used)) static void
bfa_sfp_scn(struct bfa_sfp_s *sfp, struct bfi_mbmsg_s *msg)
{
	struct bfi_sfp_scn_s *rsp = (struct bfi_sfp_scn_s *) msg;

	switch (rsp->event) {
	case BFA_SFP_SCN_INSERTED:
		sfp->state = BFA_SFP_STATE_INSERTED;
		sfp->data_valid = 0;
		bfa_sfp_scn_aen_post(sfp, rsp);
		break;
	case BFA_SFP_SCN_REMOVED:
		sfp->state = BFA_SFP_STATE_REMOVED;
		sfp->data_valid = 0;
		bfa_sfp_scn_aen_post(sfp, rsp);
		 break;
	case BFA_SFP_SCN_FAILED:
		sfp->state = BFA_SFP_STATE_FAILED;
		sfp->data_valid = 0;
		bfa_sfp_scn_aen_post(sfp, rsp);
		break;
	case BFA_SFP_SCN_UNSUPPORT:
		sfp->state = BFA_SFP_STATE_UNSUPPORT;
		bfa_sfp_scn_aen_post(sfp, rsp);
		if (!sfp->lock)
			bfa_sfp_getdata(sfp, BFI_SFP_MEM_ALL);
		break;
	case BFA_SFP_SCN_POM:
		bfa_sfp_scn_aen_post(sfp, rsp);
		break;
	case BFA_SFP_SCN_VALID:
		sfp->state = BFA_SFP_STATE_VALID;
		if (!sfp->lock)
			bfa_sfp_getdata(sfp, BFI_SFP_MEM_ALL);
		break;
	default:
		bfa_trc(sfp, rsp->event);
		WARN_ON(1);
	}
}