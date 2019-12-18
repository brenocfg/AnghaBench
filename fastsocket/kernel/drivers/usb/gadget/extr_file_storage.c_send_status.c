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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct lun {scalar_t__ sense_data; scalar_t__ sense_data_info; } ;
struct interrupt_data {void* bValue; scalar_t__ bType; void* Status; void* Residue; int /*<<< orphan*/  Tag; void* Signature; } ;
struct fsg_dev {struct fsg_buffhd* next_buffhd_to_fill; int /*<<< orphan*/  intreq_busy; TYPE_1__* intreq; int /*<<< orphan*/  intr_in; struct fsg_buffhd* intr_buffhd; int /*<<< orphan*/  bulk_in; int /*<<< orphan*/  residue; int /*<<< orphan*/  tag; scalar_t__ phase_error; scalar_t__ bad_lun_okay; struct lun* curlun; } ;
struct fsg_buffhd {scalar_t__ state; struct fsg_buffhd* next; TYPE_1__* inreq; struct interrupt_data* buf; int /*<<< orphan*/  inreq_busy; } ;
struct bulk_cs_wrap {void* bValue; scalar_t__ bType; void* Status; void* Residue; int /*<<< orphan*/  Tag; void* Signature; } ;
struct TYPE_4__ {scalar_t__ transport_type; scalar_t__ protocol_type; } ;
struct TYPE_3__ {struct fsg_buffhd* context; int /*<<< orphan*/  buf; int /*<<< orphan*/  length; scalar_t__ zero; } ;

/* Variables and functions */
 scalar_t__ ASC (scalar_t__) ; 
 void* ASCQ (scalar_t__) ; 
 scalar_t__ BUF_STATE_EMPTY ; 
 int /*<<< orphan*/  CBI_INTERRUPT_DATA_LEN ; 
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*) ; 
 int /*<<< orphan*/  SK (scalar_t__) ; 
 scalar_t__ SS_INVALID_COMMAND ; 
 scalar_t__ SS_LOGICAL_UNIT_NOT_SUPPORTED ; 
 scalar_t__ SS_NO_SENSE ; 
 int /*<<< orphan*/  USB_BULK_CS_SIG ; 
 int /*<<< orphan*/  USB_BULK_CS_WRAP_LEN ; 
 scalar_t__ USB_PR_CB ; 
 scalar_t__ USB_SC_UFI ; 
 void* USB_STATUS_FAIL ; 
 void* USB_STATUS_PASS ; 
 void* USB_STATUS_PHASE_ERROR ; 
 int /*<<< orphan*/  VDBG (struct fsg_dev*,char*,int /*<<< orphan*/ ,scalar_t__,void*,scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 TYPE_2__ mod_data ; 
 int sleep_thread (struct fsg_dev*) ; 
 int /*<<< orphan*/  start_transfer (struct fsg_dev*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ transport_is_bbb () ; 

__attribute__((used)) static int send_status(struct fsg_dev *fsg)
{
	struct lun		*curlun = fsg->curlun;
	struct fsg_buffhd	*bh;
	int			rc;
	u8			status = USB_STATUS_PASS;
	u32			sd, sdinfo = 0;

	/* Wait for the next buffer to become available */
	bh = fsg->next_buffhd_to_fill;
	while (bh->state != BUF_STATE_EMPTY) {
		rc = sleep_thread(fsg);
		if (rc)
			return rc;
	}

	if (curlun) {
		sd = curlun->sense_data;
		sdinfo = curlun->sense_data_info;
	} else if (fsg->bad_lun_okay)
		sd = SS_NO_SENSE;
	else
		sd = SS_LOGICAL_UNIT_NOT_SUPPORTED;

	if (fsg->phase_error) {
		DBG(fsg, "sending phase-error status\n");
		status = USB_STATUS_PHASE_ERROR;
		sd = SS_INVALID_COMMAND;
	} else if (sd != SS_NO_SENSE) {
		DBG(fsg, "sending command-failure status\n");
		status = USB_STATUS_FAIL;
		VDBG(fsg, "  sense data: SK x%02x, ASC x%02x, ASCQ x%02x;"
				"  info x%x\n",
				SK(sd), ASC(sd), ASCQ(sd), sdinfo);
	}

	if (transport_is_bbb()) {
		struct bulk_cs_wrap	*csw = bh->buf;

		/* Store and send the Bulk-only CSW */
		csw->Signature = cpu_to_le32(USB_BULK_CS_SIG);
		csw->Tag = fsg->tag;
		csw->Residue = cpu_to_le32(fsg->residue);
		csw->Status = status;

		bh->inreq->length = USB_BULK_CS_WRAP_LEN;
		bh->inreq->zero = 0;
		start_transfer(fsg, fsg->bulk_in, bh->inreq,
				&bh->inreq_busy, &bh->state);

	} else if (mod_data.transport_type == USB_PR_CB) {

		/* Control-Bulk transport has no status phase! */
		return 0;

	} else {			// USB_PR_CBI
		struct interrupt_data	*buf = bh->buf;

		/* Store and send the Interrupt data.  UFI sends the ASC
		 * and ASCQ bytes.  Everything else sends a Type (which
		 * is always 0) and the status Value. */
		if (mod_data.protocol_type == USB_SC_UFI) {
			buf->bType = ASC(sd);
			buf->bValue = ASCQ(sd);
		} else {
			buf->bType = 0;
			buf->bValue = status;
		}
		fsg->intreq->length = CBI_INTERRUPT_DATA_LEN;

		fsg->intr_buffhd = bh;		// Point to the right buffhd
		fsg->intreq->buf = bh->inreq->buf;
		fsg->intreq->context = bh;
		start_transfer(fsg, fsg->intr_in, fsg->intreq,
				&fsg->intreq_busy, &bh->state);
	}

	fsg->next_buffhd_to_fill = bh->next;
	return 0;
}