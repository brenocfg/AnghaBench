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
struct Scsi_Host {int host_no; int this_id; int /*<<< orphan*/  sg_tablesize; int /*<<< orphan*/  base; scalar_t__ n_io_port; int /*<<< orphan*/  io_port; int /*<<< orphan*/  irq; scalar_t__ hostdata; } ;
typedef  int off_t ;
struct TYPE_3__ {TYPE_2__* Sync; int /*<<< orphan*/  Lock; int /*<<< orphan*/  CurrentSC; scalar_t__ MmioLength; } ;
typedef  TYPE_1__ nsp_hw_data ;
struct TYPE_4__ {int SyncNegotiation; int SyncPeriod; int /*<<< orphan*/  SyncOffset; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
#define  BURST_IO32 133 
#define  BURST_IO8 132 
#define  BURST_MEM32 131 
 int EINVAL ; 
 int /*<<< orphan*/  SPRINTF (char*,...) ; 
#define  SYNC_NG 130 
#define  SYNC_NOT_YET 129 
#define  SYNC_OK 128 
 int min (int,int) ; 
 int nsp_burst_mode ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nsp_proc_info(struct Scsi_Host *host, char *buffer, char **start,
			 off_t offset, int length, int inout)
{
	int id;
	char *pos = buffer;
	int thislength;
	int speed;
	unsigned long flags;
	nsp_hw_data *data;
	int hostno;

	if (inout) {
		return -EINVAL;
	}

	hostno = host->host_no;
	data = (nsp_hw_data *)host->hostdata;


	SPRINTF("NinjaSCSI status\n\n");
	SPRINTF("Driver version:        $Revision: 1.23 $\n");
	SPRINTF("SCSI host No.:         %d\n",          hostno);
	SPRINTF("IRQ:                   %d\n",          host->irq);
	SPRINTF("IO:                    0x%lx-0x%lx\n", host->io_port, host->io_port + host->n_io_port - 1);
	SPRINTF("MMIO(virtual address): 0x%lx-0x%lx\n", host->base, host->base + data->MmioLength - 1);
	SPRINTF("sg_tablesize:          %d\n",          host->sg_tablesize);

	SPRINTF("burst transfer mode:   ");
	switch (nsp_burst_mode) {
	case BURST_IO8:
		SPRINTF("io8");
		break;
	case BURST_IO32:
		SPRINTF("io32");
		break;
	case BURST_MEM32:
		SPRINTF("mem32");
		break;
	default:
		SPRINTF("???");
		break;
	}
	SPRINTF("\n");


	spin_lock_irqsave(&(data->Lock), flags);
	SPRINTF("CurrentSC:             0x%p\n\n",      data->CurrentSC);
	spin_unlock_irqrestore(&(data->Lock), flags);

	SPRINTF("SDTR status\n");
	for(id = 0; id < ARRAY_SIZE(data->Sync); id++) {

		SPRINTF("id %d: ", id);

		if (id == host->this_id) {
			SPRINTF("----- NinjaSCSI-3 host adapter\n");
			continue;
		}

		switch(data->Sync[id].SyncNegotiation) {
		case SYNC_OK:
			SPRINTF(" sync");
			break;
		case SYNC_NG:
			SPRINTF("async");
			break;
		case SYNC_NOT_YET:
			SPRINTF(" none");
			break;
		default:
			SPRINTF("?????");
			break;
		}

		if (data->Sync[id].SyncPeriod != 0) {
			speed = 1000000 / (data->Sync[id].SyncPeriod * 4);

			SPRINTF(" transfer %d.%dMB/s, offset %d",
				speed / 1000,
				speed % 1000,
				data->Sync[id].SyncOffset
				);
		}
		SPRINTF("\n");
	}

	thislength = pos - (buffer + offset);

	if(thislength < 0) {
		*start = NULL;
                return 0;
        }


	thislength = min(thislength, length);
	*start = buffer + offset;

	return thislength;
}