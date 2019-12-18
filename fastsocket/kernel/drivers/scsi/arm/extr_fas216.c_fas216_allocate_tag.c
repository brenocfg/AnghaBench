#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int* cmnd; int tag; TYPE_1__* device; } ;
struct TYPE_6__ {int removes; int writes; int reads; int miscs; } ;
struct TYPE_7__ {TYPE_2__ stats; int /*<<< orphan*/  busyluns; } ;
struct TYPE_5__ {int current_tag; int id; scalar_t__ lun; scalar_t__ simple_tags; } ;
typedef  TYPE_3__ FAS216_Info ;

/* Variables and functions */
 int INQUIRY ; 
#define  READ_10 133 
#define  READ_12 132 
#define  READ_6 131 
 int REQUEST_SENSE ; 
#define  WRITE_10 130 
#define  WRITE_12 129 
#define  WRITE_6 128 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fas216_allocate_tag(FAS216_Info *info, struct scsi_cmnd *SCpnt)
{
#ifdef SCSI2_TAG
	/*
	 * tagged queuing - allocate a new tag to this command
	 */
	if (SCpnt->device->simple_tags && SCpnt->cmnd[0] != REQUEST_SENSE &&
	    SCpnt->cmnd[0] != INQUIRY) {
	    SCpnt->device->current_tag += 1;
		if (SCpnt->device->current_tag == 0)
		    SCpnt->device->current_tag = 1;
			SCpnt->tag = SCpnt->device->current_tag;
	} else
#endif
		set_bit(SCpnt->device->id * 8 + SCpnt->device->lun, info->busyluns);

	info->stats.removes += 1;
	switch (SCpnt->cmnd[0]) {
	case WRITE_6:
	case WRITE_10:
	case WRITE_12:
		info->stats.writes += 1;
		break;
	case READ_6:
	case READ_10:
	case READ_12:
		info->stats.reads += 1;
		break;
	default:
		info->stats.miscs += 1;
		break;
	}
}