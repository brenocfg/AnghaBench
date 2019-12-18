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
struct TYPE_10__ {int /*<<< orphan*/  msgs; } ;
struct TYPE_11__ {TYPE_4__ scsi; TYPE_3__* SCpnt; TYPE_1__* device; } ;
struct TYPE_9__ {scalar_t__* cmnd; TYPE_2__* device; scalar_t__ tag; } ;
struct TYPE_8__ {size_t id; int /*<<< orphan*/  lun; } ;
struct TYPE_7__ {scalar_t__ sync_state; int /*<<< orphan*/  disconnect_ok; } ;
typedef  TYPE_5__ AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DEVICE_RESET ; 
 int /*<<< orphan*/  EXTENDED_MESSAGE ; 
 int /*<<< orphan*/  EXTENDED_SDTR ; 
 unsigned int HEAD_OF_QUEUE_TAG ; 
 int /*<<< orphan*/  IDENTIFY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INQUIRY ; 
 scalar_t__ REQUEST_SENSE ; 
 unsigned int SIMPLE_QUEUE_TAG ; 
 scalar_t__ SYNC_NEGOCIATE ; 
 scalar_t__ SYNC_SENT_REQUEST ; 
 scalar_t__ TEST_UNIT_READY ; 
 int /*<<< orphan*/  acornscsi_abortcmd (scalar_t__) ; 
 scalar_t__ cmd_aborted ; 
 scalar_t__ cmd_reset ; 
 int /*<<< orphan*/  msgqueue_addmsg (int /*<<< orphan*/ *,int,unsigned int,...) ; 
 int sdtr_period ; 
 int /*<<< orphan*/  sdtr_size ; 

__attribute__((used)) static
void acornscsi_buildmessages(AS_Host *host)
{
#if 0
    /* does the device need resetting? */
    if (cmd_reset) {
	msgqueue_addmsg(&host->scsi.msgs, 1, BUS_DEVICE_RESET);
	return;
    }
#endif

    msgqueue_addmsg(&host->scsi.msgs, 1,
		     IDENTIFY(host->device[host->SCpnt->device->id].disconnect_ok,
			     host->SCpnt->device->lun));

#if 0
    /* does the device need the current command aborted */
    if (cmd_aborted) {
	acornscsi_abortcmd(host->SCpnt->tag);
	return;
    }
#endif

#ifdef CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
    if (host->SCpnt->tag) {
	unsigned int tag_type;

	if (host->SCpnt->cmnd[0] == REQUEST_SENSE ||
	    host->SCpnt->cmnd[0] == TEST_UNIT_READY ||
	    host->SCpnt->cmnd[0] == INQUIRY)
	    tag_type = HEAD_OF_QUEUE_TAG;
	else
	    tag_type = SIMPLE_QUEUE_TAG;
	msgqueue_addmsg(&host->scsi.msgs, 2, tag_type, host->SCpnt->tag);
    }
#endif

#ifdef CONFIG_SCSI_ACORNSCSI_SYNC
    if (host->device[host->SCpnt->device->id].sync_state == SYNC_NEGOCIATE) {
	host->device[host->SCpnt->device->id].sync_state = SYNC_SENT_REQUEST;
	msgqueue_addmsg(&host->scsi.msgs, 5,
			 EXTENDED_MESSAGE, 3, EXTENDED_SDTR,
			 sdtr_period / 4, sdtr_size);
    }
#endif
}