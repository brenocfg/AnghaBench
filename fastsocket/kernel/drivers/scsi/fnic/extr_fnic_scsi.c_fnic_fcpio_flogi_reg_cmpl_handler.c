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
typedef  int /*<<< orphan*/  u8 ;
struct fnic {scalar_t__ state; int /*<<< orphan*/  fnic_lock; int /*<<< orphan*/  frame_work; scalar_t__ stop_rx_link_events; TYPE_1__* lport; } ;
struct fcpio_tag {int dummy; } ;
struct fcpio_fw_req {int /*<<< orphan*/  hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ FNIC_IN_ETH_MODE ; 
 scalar_t__ FNIC_IN_ETH_TRANS_FC_MODE ; 
 scalar_t__ FNIC_IN_FC_MODE ; 
 int /*<<< orphan*/  FNIC_SCSI_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  fcpio_header_dec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fcpio_tag*) ; 
 int /*<<< orphan*/  fnic_event_queue ; 
 int /*<<< orphan*/  fnic_fcpio_status_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_flush_tx (struct fnic*) ; 
 int /*<<< orphan*/  fnic_state_to_str (scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fnic_fcpio_flogi_reg_cmpl_handler(struct fnic *fnic,
					     struct fcpio_fw_req *desc)
{
	u8 type;
	u8 hdr_status;
	struct fcpio_tag tag;
	int ret = 0;
	unsigned long flags;

	fcpio_header_dec(&desc->hdr, &type, &hdr_status, &tag);

	/* Update fnic state based on status of flogi reg completion */
	spin_lock_irqsave(&fnic->fnic_lock, flags);

	if (fnic->state == FNIC_IN_ETH_TRANS_FC_MODE) {

		/* Check flogi registration completion status */
		if (!hdr_status) {
			FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				      "flog reg succeeded\n");
			fnic->state = FNIC_IN_FC_MODE;
		} else {
			FNIC_SCSI_DBG(KERN_DEBUG,
				      fnic->lport->host,
				      "fnic flogi reg :failed %s\n",
				      fnic_fcpio_status_to_str(hdr_status));
			fnic->state = FNIC_IN_ETH_MODE;
			ret = -1;
		}
	} else {
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Unexpected fnic state %s while"
			      " processing flogi reg completion\n",
			      fnic_state_to_str(fnic->state));
		ret = -1;
	}

	if (!ret) {
		if (fnic->stop_rx_link_events) {
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			goto reg_cmpl_handler_end;
		}
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);

		fnic_flush_tx(fnic);
		queue_work(fnic_event_queue, &fnic->frame_work);
	} else {
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
	}

reg_cmpl_handler_end:
	return ret;
}