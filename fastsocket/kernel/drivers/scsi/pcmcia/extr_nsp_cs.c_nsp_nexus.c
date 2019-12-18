#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int SyncRegister; int AckWidth; } ;
typedef  TYPE_3__ sync_data ;
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_9__ {scalar_t__ FifoCount; void* TransferMode; TYPE_3__* Sync; } ;
typedef  TYPE_4__ nsp_hw_data ;
struct TYPE_7__ {TYPE_1__* host; } ;
struct TYPE_6__ {unsigned int io_port; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACKWIDTH ; 
 int ACK_COUNTER_CLEAR ; 
 scalar_t__ BURST_IO32 ; 
 scalar_t__ BURST_MEM32 ; 
 int HOST_COUNTER_CLEAR ; 
 void* MODE_IO32 ; 
 void* MODE_IO8 ; 
 void* MODE_MEM32 ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  POINTERCLR ; 
 int POINTER_CLEAR ; 
 int REQ_COUNTER_CLEAR ; 
 int /*<<< orphan*/  SYNCREG ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ nsp_burst_mode ; 
 int /*<<< orphan*/  nsp_index_write (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsp_setup_fifo (TYPE_4__*,int /*<<< orphan*/ ) ; 
 unsigned char scmd_id (struct scsi_cmnd*) ; 
 int scsi_get_resid (struct scsi_cmnd*) ; 

__attribute__((used)) static int nsp_nexus(struct scsi_cmnd *SCpnt)
{
	unsigned int   base   = SCpnt->device->host->io_port;
	unsigned char  target = scmd_id(SCpnt);
//	unsigned char  lun    = SCpnt->device->lun;
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	sync_data     *sync   = &(data->Sync[target]);

	//nsp_dbg(NSP_DEBUG_DATA_IO, "in SCpnt=0x%p", SCpnt);

	/* setup synch transfer registers */
	nsp_index_write(base, SYNCREG,	sync->SyncRegister);
	nsp_index_write(base, ACKWIDTH, sync->AckWidth);

	if (scsi_get_resid(SCpnt) % 4 != 0 ||
	    scsi_get_resid(SCpnt) <= PAGE_SIZE ) {
		data->TransferMode = MODE_IO8;
	} else if (nsp_burst_mode == BURST_MEM32) {
		data->TransferMode = MODE_MEM32;
	} else if (nsp_burst_mode == BURST_IO32) {
		data->TransferMode = MODE_IO32;
	} else {
		data->TransferMode = MODE_IO8;
	}

	/* setup pdma fifo */
	nsp_setup_fifo(data, TRUE);

	/* clear ack counter */
 	data->FifoCount = 0;
	nsp_index_write(base, POINTERCLR, POINTER_CLEAR	    |
					  ACK_COUNTER_CLEAR |
					  REQ_COUNTER_CLEAR |
					  HOST_COUNTER_CLEAR);

	return 0;
}