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
struct ub_scsi_cmd {scalar_t__ dir; int /*<<< orphan*/  state; int /*<<< orphan*/  cdb; int /*<<< orphan*/  cdb_len; TYPE_1__* lun; int /*<<< orphan*/  len; int /*<<< orphan*/  tag; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct bulk_cb_wrap {int Flags; int /*<<< orphan*/  CDB; int /*<<< orphan*/  Length; int /*<<< orphan*/  Lun; void* DataTransferLength; int /*<<< orphan*/  Tag; void* Signature; } ;
struct ub_dev {TYPE_2__ work_timer; int /*<<< orphan*/  work_done; int /*<<< orphan*/  work_urb; int /*<<< orphan*/  send_bulk_pipe; int /*<<< orphan*/  dev; int /*<<< orphan*/  last_pipe; int /*<<< orphan*/  top_sense; struct bulk_cb_wrap work_bcb; } ;
struct TYPE_3__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  UB_CMDST_CMD ; 
 scalar_t__ UB_DIR_READ ; 
 int /*<<< orphan*/  UB_INIT_COMPLETION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UB_MAX_CDB_SIZE ; 
 int /*<<< orphan*/  UB_SENSE_SIZE ; 
 scalar_t__ UB_URB_TIMEOUT ; 
 int /*<<< orphan*/  US_BULK_CB_SIGN ; 
 int /*<<< orphan*/  US_BULK_CB_WRAP_LEN ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ub_urb_complete ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bulk_cb_wrap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ub_dev*) ; 
 int usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ub_scsi_cmd_start(struct ub_dev *sc, struct ub_scsi_cmd *cmd)
{
	struct bulk_cb_wrap *bcb;
	int rc;

	bcb = &sc->work_bcb;

	/*
	 * ``If the allocation length is eighteen or greater, and a device
	 * server returns less than eithteen bytes of data, the application
	 * client should assume that the bytes not transferred would have been
	 * zeroes had the device server returned those bytes.''
	 *
	 * We zero sense for all commands so that when a packet request
	 * fails it does not return a stale sense.
	 */
	memset(&sc->top_sense, 0, UB_SENSE_SIZE);

	/* set up the command wrapper */
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->Tag = cmd->tag;		/* Endianness is not important */
	bcb->DataTransferLength = cpu_to_le32(cmd->len);
	bcb->Flags = (cmd->dir == UB_DIR_READ) ? 0x80 : 0;
	bcb->Lun = (cmd->lun != NULL) ? cmd->lun->num : 0;
	bcb->Length = cmd->cdb_len;

	/* copy the command payload */
	memcpy(bcb->CDB, cmd->cdb, UB_MAX_CDB_SIZE);

	UB_INIT_COMPLETION(sc->work_done);

	sc->last_pipe = sc->send_bulk_pipe;
	usb_fill_bulk_urb(&sc->work_urb, sc->dev, sc->send_bulk_pipe,
	    bcb, US_BULK_CB_WRAP_LEN, ub_urb_complete, sc);

	if ((rc = usb_submit_urb(&sc->work_urb, GFP_ATOMIC)) != 0) {
		/* XXX Clear stalls */
		ub_complete(&sc->work_done);
		return rc;
	}

	sc->work_timer.expires = jiffies + UB_URB_TIMEOUT;
	add_timer(&sc->work_timer);

	cmd->state = UB_CMDST_CMD;
	return 0;
}