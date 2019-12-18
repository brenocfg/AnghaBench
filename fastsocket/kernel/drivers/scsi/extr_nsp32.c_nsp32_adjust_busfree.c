#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32_le ;
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_11__ {void* len; void* addr; } ;
typedef  TYPE_5__ nsp32_sgtable ;
struct TYPE_12__ {int cur_entry; TYPE_4__* cur_lunt; } ;
typedef  TYPE_6__ nsp32_hw_data ;
struct TYPE_10__ {int sg_num; TYPE_3__* sglun; } ;
struct TYPE_9__ {TYPE_5__* sgt; } ;
struct TYPE_8__ {TYPE_1__* host; } ;
struct TYPE_7__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NSP32_DEBUG_SGLIST ; 
 unsigned int SGTEND ; 
 void* cpu_to_le32 (unsigned int) ; 
 unsigned int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*) ; 
 unsigned int scsi_get_resid (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,unsigned int) ; 

__attribute__((used)) static void nsp32_adjust_busfree(struct scsi_cmnd *SCpnt, unsigned int s_sacklen)
{
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	int                   old_entry = data->cur_entry;
	int                   new_entry;
	int                   sg_num = data->cur_lunt->sg_num;
	nsp32_sgtable *sgt    = data->cur_lunt->sglun->sgt;
	unsigned int          restlen, sentlen;
	u32_le                len, addr;

	nsp32_dbg(NSP32_DEBUG_SGLIST, "old resid=0x%x", scsi_get_resid(SCpnt));

	/* adjust saved SACK count with 4 byte start address boundary */
	s_sacklen -= le32_to_cpu(sgt[old_entry].addr) & 3;

	/*
	 * calculate new_entry from sack count and each sgt[].len 
	 * calculate the byte which is intent to send
	 */
	sentlen = 0;
	for (new_entry = old_entry; new_entry < sg_num; new_entry++) {
		sentlen += (le32_to_cpu(sgt[new_entry].len) & ~SGTEND);
		if (sentlen > s_sacklen) {
			break;
		}
	}

	/* all sgt is processed */
	if (new_entry == sg_num) {
		goto last;
	}

	if (sentlen == s_sacklen) {
		/* XXX: confirm it's ok or not */
		/* In this case, it's ok because we are at 
		   the head element of the sg. restlen is correctly calculated. */
	}

	/* calculate the rest length for transfering */
	restlen = sentlen - s_sacklen;

	/* update adjusting current SG table entry */
	len  = le32_to_cpu(sgt[new_entry].len);
	addr = le32_to_cpu(sgt[new_entry].addr);
	addr += (len - restlen);
	sgt[new_entry].addr = cpu_to_le32(addr);
	sgt[new_entry].len  = cpu_to_le32(restlen);

	/* set cur_entry with new_entry */
	data->cur_entry = new_entry;
 
	return;

 last:
	if (scsi_get_resid(SCpnt) < sentlen) {
		nsp32_msg(KERN_ERR, "resid underflow");
	}

	scsi_set_resid(SCpnt, scsi_get_resid(SCpnt) - sentlen);
	nsp32_dbg(NSP32_DEBUG_SGLIST, "new resid=0x%x", scsi_get_resid(SCpnt));

	/* update hostdata and lun */

	return;
}