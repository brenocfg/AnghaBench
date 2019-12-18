#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_6__ {int MsgLen; } ;
typedef  TYPE_3__ nsp_hw_data ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUSMON_REQ ; 
 int /*<<< orphan*/  BUSPHASE_MESSAGE_OUT ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  NSP_DEBUG_MSGOUTOCCUR ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*) ; 
 int nsp_expect_signal (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp_msg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nsp_xfer (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nsp_message_out(struct scsi_cmnd *SCpnt)
{
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	int ret = 1;
	int len = data->MsgLen;

	/*
	 * XXX: NSP QUIRK
	 * NSP invoke interrupts only in the case of scsi phase changes,
	 * therefore we should poll the scsi phase here to catch 
	 * the next "msg out" if exists (no scsi phase changes).
	 */

	nsp_dbg(NSP_DEBUG_MSGOUTOCCUR, "msgout loop");
	do {
		if (nsp_xfer(SCpnt, BUSPHASE_MESSAGE_OUT)) {
			nsp_msg(KERN_DEBUG, "msgout: xfer short");
		}

		/* catch a next signal */
		ret = nsp_expect_signal(SCpnt, BUSPHASE_MESSAGE_OUT, BUSMON_REQ);
	} while (ret > 0 && len-- > 0);

}