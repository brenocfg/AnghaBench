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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vnic_wq_copy {int dummy; } ;
struct fnic_io_req {int /*<<< orphan*/  port_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  ed_tov; int /*<<< orphan*/  ra_tov; } ;
struct fnic {scalar_t__* wq_copy_desc_low; int /*<<< orphan*/  in_flight; int /*<<< orphan*/ * wq_copy_lock; TYPE_2__ config; TYPE_1__* lport; struct vnic_wq_copy* wq_copy; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; } ;
struct TYPE_3__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNIC_FLAGS_IO_BLOCKED ; 
 int /*<<< orphan*/  FNIC_SCSI_DBG (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 int FNIC_TAG_ABORT ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnic_chk_state_flags_locked (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_queue_wq_copy_desc_itmf (struct vnic_wq_copy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_wq_copy_descs (struct fnic*,struct vnic_wq_copy*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vnic_wq_copy_desc_avail (struct vnic_wq_copy*) ; 

__attribute__((used)) static inline int fnic_queue_abort_io_req(struct fnic *fnic, int tag,
					  u32 task_req, u8 *fc_lun,
					  struct fnic_io_req *io_req)
{
	struct vnic_wq_copy *wq = &fnic->wq_copy[0];
	struct Scsi_Host *host = fnic->lport->host;
	unsigned long flags;

	spin_lock_irqsave(host->host_lock, flags);
	if (unlikely(fnic_chk_state_flags_locked(fnic,
						FNIC_FLAGS_IO_BLOCKED))) {
		spin_unlock_irqrestore(host->host_lock, flags);
		return 1;
	} else
		atomic_inc(&fnic->in_flight);
	spin_unlock_irqrestore(host->host_lock, flags);

	spin_lock_irqsave(&fnic->wq_copy_lock[0], flags);

	if (vnic_wq_copy_desc_avail(wq) <= fnic->wq_copy_desc_low[0])
		free_wq_copy_descs(fnic, wq);

	if (!vnic_wq_copy_desc_avail(wq)) {
		spin_unlock_irqrestore(&fnic->wq_copy_lock[0], flags);
		atomic_dec(&fnic->in_flight);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			"fnic_queue_abort_io_req: failure: no descriptors\n");
		return 1;
	}
	fnic_queue_wq_copy_desc_itmf(wq, tag | FNIC_TAG_ABORT,
				     0, task_req, tag, fc_lun, io_req->port_id,
				     fnic->config.ra_tov, fnic->config.ed_tov);

	spin_unlock_irqrestore(&fnic->wq_copy_lock[0], flags);
	atomic_dec(&fnic->in_flight);

	return 0;
}