#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  msgs; int /*<<< orphan*/  phase; } ;
struct TYPE_6__ {TYPE_1__ scsi; } ;
typedef  TYPE_2__ AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT ; 
 int /*<<< orphan*/  ABORT_TAG ; 
 int /*<<< orphan*/  CMND_ASSERTATN ; 
 int /*<<< orphan*/  PHASE_ABORTED ; 
 int /*<<< orphan*/  SBIC_CMND ; 
 int /*<<< orphan*/  msgqueue_addmsg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  msgqueue_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbic_arm_write (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void acornscsi_abortcmd(AS_Host *host, unsigned char tag)
{
    host->scsi.phase = PHASE_ABORTED;
    sbic_arm_write(host, SBIC_CMND, CMND_ASSERTATN);

    msgqueue_flush(&host->scsi.msgs);
#ifdef CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
    if (tag)
	msgqueue_addmsg(&host->scsi.msgs, 2, ABORT_TAG, tag);
    else
#endif
	msgqueue_addmsg(&host->scsi.msgs, 1, ABORT);
}