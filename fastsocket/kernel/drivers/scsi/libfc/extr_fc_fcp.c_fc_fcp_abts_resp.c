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
struct fc_frame_header {int fh_r_ctl; } ;
struct fc_frame {int dummy; } ;
struct fc_fcp_pkt {int /*<<< orphan*/  tm_done; scalar_t__ wait_for_comp; int /*<<< orphan*/  state; } ;
struct fc_ba_rjt {int /*<<< orphan*/  br_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_BA_RJT_LOG_ERR ; 
#define  FC_RCTL_BA_ACC 129 
#define  FC_RCTL_BA_RJT 128 
 int /*<<< orphan*/  FC_SRB_ABORTED ; 
 int /*<<< orphan*/  FC_SRB_ABORT_PENDING ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_fcp_complete_locked (struct fc_fcp_pkt*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 struct fc_ba_rjt* fc_frame_payload_get (struct fc_frame*,int) ; 

__attribute__((used)) static void fc_fcp_abts_resp(struct fc_fcp_pkt *fsp, struct fc_frame *fp)
{
	int ba_done = 1;
	struct fc_ba_rjt *brp;
	struct fc_frame_header *fh;

	fh = fc_frame_header_get(fp);
	switch (fh->fh_r_ctl) {
	case FC_RCTL_BA_ACC:
		break;
	case FC_RCTL_BA_RJT:
		brp = fc_frame_payload_get(fp, sizeof(*brp));
		if (brp && brp->br_reason == FC_BA_RJT_LOG_ERR)
			break;
		/* fall thru */
	default:
		/*
		 * we will let the command timeout
		 * and scsi-ml recover in this case,
		 * therefore cleared the ba_done flag.
		 */
		ba_done = 0;
	}

	if (ba_done) {
		fsp->state |= FC_SRB_ABORTED;
		fsp->state &= ~FC_SRB_ABORT_PENDING;

		if (fsp->wait_for_comp)
			complete(&fsp->tm_done);
		else
			fc_fcp_complete_locked(fsp);
	}
}