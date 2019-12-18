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
struct fc_fcp_pkt {int wait_for_comp; int state; int /*<<< orphan*/  scsi_pkt_lock; int /*<<< orphan*/  tm_done; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  FC_FCP_DBG (struct fc_fcp_pkt*,char*) ; 
 int /*<<< orphan*/  FC_SCSI_TM_TOV ; 
 int FC_SRB_ABORTED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  fc_fcp_complete_locked (struct fc_fcp_pkt*) ; 
 scalar_t__ fc_fcp_send_abort (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc_fcp_pkt_abort(struct fc_fcp_pkt *fsp)
{
	int rc = FAILED;
	unsigned long ticks_left;

	if (fc_fcp_send_abort(fsp))
		return FAILED;

	init_completion(&fsp->tm_done);
	fsp->wait_for_comp = 1;

	spin_unlock_bh(&fsp->scsi_pkt_lock);
	ticks_left = wait_for_completion_timeout(&fsp->tm_done,
							FC_SCSI_TM_TOV);
	spin_lock_bh(&fsp->scsi_pkt_lock);
	fsp->wait_for_comp = 0;

	if (!ticks_left) {
		FC_FCP_DBG(fsp, "target abort cmd  failed\n");
	} else if (fsp->state & FC_SRB_ABORTED) {
		FC_FCP_DBG(fsp, "target abort cmd  passed\n");
		rc = SUCCESS;
		fc_fcp_complete_locked(fsp);
	}

	return rc;
}