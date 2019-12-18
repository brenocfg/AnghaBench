#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct adpt_device {struct adpt_device* next_lun; TYPE_5__* pScsi_dev; scalar_t__ scsi_lun; scalar_t__ scsi_id; scalar_t__ scsi_channel; TYPE_3__* pI2o_dev; } ;
struct Scsi_Host {int host_no; int irq; int can_queue; int sg_tablesize; } ;
typedef  int off_t ;
struct TYPE_10__ {char* detail; char* name; TYPE_1__* channel; scalar_t__ reply_fifo_size; struct Scsi_Host* host; struct TYPE_10__* next; } ;
typedef  TYPE_4__ adpt_hba ;
struct TYPE_11__ {char* vendor; char* rev; } ;
struct TYPE_8__ {int tid; } ;
struct TYPE_9__ {TYPE_2__ lct_data; } ;
struct TYPE_7__ {struct adpt_device** device; } ;

/* Variables and functions */
 char* DPT_I2O_VERSION ; 
 int EINVAL ; 
 int MAX_CHANNEL ; 
 int MAX_ID ; 
 int TRUE ; 
 int /*<<< orphan*/  adpt_configuration_lock ; 
 TYPE_4__* hba_chain ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_device_online (TYPE_5__*) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int adpt_proc_info(struct Scsi_Host *host, char *buffer, char **start, off_t offset,
		  int length, int inout)
{
	struct adpt_device* d;
	int id;
	int chan;
	int len = 0;
	int begin = 0;
	int pos = 0;
	adpt_hba* pHba;
	int unit;

	*start = buffer;
	if (inout == TRUE) {
		/*
		 * The user has done a write and wants us to take the
		 * data in the buffer and do something with it.
		 * proc_scsiwrite calls us with inout = 1
		 *
		 * Read data from buffer (writing to us) - NOT SUPPORTED
		 */
		return -EINVAL;
	}

	/*
	 * inout = 0 means the user has done a read and wants information
	 * returned, so we write information about the cards into the buffer
	 * proc_scsiread() calls us with inout = 0
	 */

	// Find HBA (host bus adapter) we are looking for
	mutex_lock(&adpt_configuration_lock);
	for (pHba = hba_chain; pHba; pHba = pHba->next) {
		if (pHba->host == host) {
			break;	/* found adapter */
		}
	}
	mutex_unlock(&adpt_configuration_lock);
	if (pHba == NULL) {
		return 0;
	}
	host = pHba->host;

	len  = sprintf(buffer    , "Adaptec I2O RAID Driver Version: %s\n\n", DPT_I2O_VERSION);
	len += sprintf(buffer+len, "%s\n", pHba->detail);
	len += sprintf(buffer+len, "SCSI Host=scsi%d  Control Node=/dev/%s  irq=%d\n", 
			pHba->host->host_no, pHba->name, host->irq);
	len += sprintf(buffer+len, "\tpost fifo size  = %d\n\treply fifo size = %d\n\tsg table size   = %d\n\n",
			host->can_queue, (int) pHba->reply_fifo_size , host->sg_tablesize);

	pos = begin + len;

	/* CHECKPOINT */
	if(pos > offset + length) {
		goto stop_output;
	}
	if(pos <= offset) {
		/*
		 * If we haven't even written to where we last left
		 * off (the last time we were called), reset the 
		 * beginning pointer.
		 */
		len = 0;
		begin = pos;
	}
	len +=  sprintf(buffer+len, "Devices:\n");
	for(chan = 0; chan < MAX_CHANNEL; chan++) {
		for(id = 0; id < MAX_ID; id++) {
			d = pHba->channel[chan].device[id];
			while(d){
				len += sprintf(buffer+len,"\t%-24.24s", d->pScsi_dev->vendor);
				len += sprintf(buffer+len," Rev: %-8.8s\n", d->pScsi_dev->rev);
				pos = begin + len;


				/* CHECKPOINT */
				if(pos > offset + length) {
					goto stop_output;
				}
				if(pos <= offset) {
					len = 0;
					begin = pos;
				}

				unit = d->pI2o_dev->lct_data.tid;
				len += sprintf(buffer+len, "\tTID=%d, (Channel=%d, Target=%d, Lun=%d)  (%s)\n\n",
					       unit, (int)d->scsi_channel, (int)d->scsi_id, (int)d->scsi_lun,
					       scsi_device_online(d->pScsi_dev)? "online":"offline"); 
				pos = begin + len;

				/* CHECKPOINT */
				if(pos > offset + length) {
					goto stop_output;
				}
				if(pos <= offset) {
					len = 0;
					begin = pos;
				}

				d = d->next_lun;
			}
		}
	}

	/*
	 * begin is where we last checked our position with regards to offset
	 * begin is always less than offset.  len is relative to begin.  It
	 * is the number of bytes written past begin
	 *
	 */
stop_output:
	/* stop the output and calculate the correct length */
	*(buffer + len) = '\0';

	*start = buffer + (offset - begin);	/* Start of wanted data */
	len -= (offset - begin);
	if(len > length) {
		len = length;
	} else if(len < 0){
		len = 0;
		**start = '\0';
	}
	return len;
}