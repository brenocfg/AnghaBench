#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_lun {int dummy; } ;
struct TYPE_8__ {int (* fcp_cmd_send ) (struct fc_lport*,struct fc_fcp_pkt*,int /*<<< orphan*/ ) ;} ;
struct fc_lport {TYPE_3__ tt; } ;
struct TYPE_7__ {int fc_flags; int /*<<< orphan*/  fc_cdb; scalar_t__ fc_lun; int /*<<< orphan*/  fc_dl; } ;
struct fc_fcp_pkt {int req_flags; int /*<<< orphan*/  list; TYPE_5__* cmd; TYPE_2__ cdb_cmd; int /*<<< orphan*/  data_len; } ;
struct fc_fcp_internal {int /*<<< orphan*/  scsi_queue_lock; int /*<<< orphan*/  scsi_pkt_queue; } ;
struct TYPE_9__ {char* ptr; } ;
struct TYPE_10__ {TYPE_4__ SCp; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; TYPE_1__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int FCP_CFL_LEN_MASK ; 
 int /*<<< orphan*/  fc_fcp_recv ; 
 struct fc_fcp_internal* fc_get_scsi_internal (struct fc_lport*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct fc_lport*,struct fc_fcp_pkt*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int fc_fcp_pkt_send(struct fc_lport *lport, struct fc_fcp_pkt *fsp)
{
	struct fc_fcp_internal *si = fc_get_scsi_internal(lport);
	unsigned long flags;
	int rc;

	fsp->cmd->SCp.ptr = (char *)fsp;
	fsp->cdb_cmd.fc_dl = htonl(fsp->data_len);
	fsp->cdb_cmd.fc_flags = fsp->req_flags & ~FCP_CFL_LEN_MASK;

	int_to_scsilun(fsp->cmd->device->lun,
		       (struct scsi_lun *)fsp->cdb_cmd.fc_lun);
	memcpy(fsp->cdb_cmd.fc_cdb, fsp->cmd->cmnd, fsp->cmd->cmd_len);

	spin_lock_irqsave(&si->scsi_queue_lock, flags);
	list_add_tail(&fsp->list, &si->scsi_pkt_queue);
	spin_unlock_irqrestore(&si->scsi_queue_lock, flags);
	rc = lport->tt.fcp_cmd_send(lport, fsp, fc_fcp_recv);
	if (unlikely(rc)) {
		spin_lock_irqsave(&si->scsi_queue_lock, flags);
		fsp->cmd->SCp.ptr = NULL;
		list_del(&fsp->list);
		spin_unlock_irqrestore(&si->scsi_queue_lock, flags);
	}

	return rc;
}