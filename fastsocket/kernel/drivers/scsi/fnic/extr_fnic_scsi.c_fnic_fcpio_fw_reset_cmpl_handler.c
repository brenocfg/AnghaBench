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
struct fnic {scalar_t__ state; int /*<<< orphan*/  fnic_lock; int /*<<< orphan*/  tx_queue; scalar_t__ remove_wait; TYPE_1__* lport; } ;
struct fcpio_tag {int dummy; } ;
struct fcpio_fw_req {int /*<<< orphan*/  hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNIC_FLAGS_FWRESET ; 
 scalar_t__ FNIC_IN_ETH_MODE ; 
 scalar_t__ FNIC_IN_FC_MODE ; 
 scalar_t__ FNIC_IN_FC_TRANS_ETH_MODE ; 
 int /*<<< orphan*/  FNIC_SCSI_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  SCSI_NO_TAG ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  fcpio_header_dec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fcpio_tag*) ; 
 int /*<<< orphan*/  fnic_cleanup_io (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_clear_state_flags (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_fcpio_status_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_flush_tx (struct fnic*) ; 
 int /*<<< orphan*/  fnic_state_to_str (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fnic_fcpio_fw_reset_cmpl_handler(struct fnic *fnic,
					    struct fcpio_fw_req *desc)
{
	u8 type;
	u8 hdr_status;
	struct fcpio_tag tag;
	int ret = 0;
	unsigned long flags;

	fcpio_header_dec(&desc->hdr, &type, &hdr_status, &tag);

	/* Clean up all outstanding io requests */
	fnic_cleanup_io(fnic, SCSI_NO_TAG);

	spin_lock_irqsave(&fnic->fnic_lock, flags);

	/* fnic should be in FC_TRANS_ETH_MODE */
	if (fnic->state == FNIC_IN_FC_TRANS_ETH_MODE) {
		/* Check status of reset completion */
		if (!hdr_status) {
			FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				      "reset cmpl success\n");
			/* Ready to send flogi out */
			fnic->state = FNIC_IN_ETH_MODE;
		} else {
			FNIC_SCSI_DBG(KERN_DEBUG,
				      fnic->lport->host,
				      "fnic fw_reset : failed %s\n",
				      fnic_fcpio_status_to_str(hdr_status));

			/*
			 * Unable to change to eth mode, cannot send out flogi
			 * Change state to fc mode, so that subsequent Flogi
			 * requests from libFC will cause more attempts to
			 * reset the firmware. Free the cached flogi
			 */
			fnic->state = FNIC_IN_FC_MODE;
			ret = -1;
		}
	} else {
		FNIC_SCSI_DBG(KERN_DEBUG,
			      fnic->lport->host,
			      "Unexpected state %s while processing"
			      " reset cmpl\n", fnic_state_to_str(fnic->state));
		ret = -1;
	}

	/* Thread removing device blocks till firmware reset is complete */
	if (fnic->remove_wait)
		complete(fnic->remove_wait);

	/*
	 * If fnic is being removed, or fw reset failed
	 * free the flogi frame. Else, send it out
	 */
	if (fnic->remove_wait || ret) {
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		skb_queue_purge(&fnic->tx_queue);
		goto reset_cmpl_handler_end;
	}

	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	fnic_flush_tx(fnic);

 reset_cmpl_handler_end:
	fnic_clear_state_flags(fnic, FNIC_FLAGS_FWRESET);

	return ret;
}