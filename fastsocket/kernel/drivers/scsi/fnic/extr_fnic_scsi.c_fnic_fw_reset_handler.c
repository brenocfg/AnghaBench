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
struct vnic_wq_copy {int dummy; } ;
struct fnic {scalar_t__* wq_copy_desc_low; TYPE_1__* lport; int /*<<< orphan*/ * wq_copy_lock; int /*<<< orphan*/  in_flight; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  frame_queue; struct vnic_wq_copy* wq_copy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  FNIC_FLAGS_FWRESET ; 
 int /*<<< orphan*/  FNIC_SCSI_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  SCSI_NO_TAG ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnic_clear_state_flags (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_queue_wq_copy_desc_fw_reset (struct vnic_wq_copy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_set_state_flags (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_wq_copy_descs (struct fnic*,struct vnic_wq_copy*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ vnic_wq_copy_desc_avail (struct vnic_wq_copy*) ; 

int fnic_fw_reset_handler(struct fnic *fnic)
{
	struct vnic_wq_copy *wq = &fnic->wq_copy[0];
	int ret = 0;
	unsigned long flags;

	/* indicate fwreset to io path */
	fnic_set_state_flags(fnic, FNIC_FLAGS_FWRESET);

	skb_queue_purge(&fnic->frame_queue);
	skb_queue_purge(&fnic->tx_queue);

	/* wait for io cmpl */
	while (atomic_read(&fnic->in_flight))
		schedule_timeout(msecs_to_jiffies(1));

	spin_lock_irqsave(&fnic->wq_copy_lock[0], flags);

	if (vnic_wq_copy_desc_avail(wq) <= fnic->wq_copy_desc_low[0])
		free_wq_copy_descs(fnic, wq);

	if (!vnic_wq_copy_desc_avail(wq))
		ret = -EAGAIN;
	else
		fnic_queue_wq_copy_desc_fw_reset(wq, SCSI_NO_TAG);

	spin_unlock_irqrestore(&fnic->wq_copy_lock[0], flags);

	if (!ret)
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Issued fw reset\n");
	else {
		fnic_clear_state_flags(fnic, FNIC_FLAGS_FWRESET);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Failed to issue fw reset\n");
	}

	return ret;
}