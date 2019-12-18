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
struct fc_frame {int dummy; } ;
struct fc_fcp_pkt {int /*<<< orphan*/  status_code; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_CMD_PLOGO ; 
 int FC_EX_CLOSED ; 
 int /*<<< orphan*/  FC_SRB_ABORT_PENDING ; 
 int PTR_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_fcp_complete_locked (struct fc_fcp_pkt*) ; 
 scalar_t__ fc_fcp_lock_pkt (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_retry_cmd (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_unlock_pkt (struct fc_fcp_pkt*) ; 

__attribute__((used)) static void fc_fcp_error(struct fc_fcp_pkt *fsp, struct fc_frame *fp)
{
	int error = PTR_ERR(fp);

	if (fc_fcp_lock_pkt(fsp))
		return;

	if (error == -FC_EX_CLOSED) {
		fc_fcp_retry_cmd(fsp);
		goto unlock;
	}

	/*
	 * clear abort pending, because the lower layer
	 * decided to force completion.
	 */
	fsp->state &= ~FC_SRB_ABORT_PENDING;
	fsp->status_code = FC_CMD_PLOGO;
	fc_fcp_complete_locked(fsp);
unlock:
	fc_fcp_unlock_pkt(fsp);
}