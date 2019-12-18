#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {scalar_t__ cmd_len; int /*<<< orphan*/  cmnd; } ;
struct TYPE_10__ {scalar_t__ sent_command; } ;
struct TYPE_12__ {int /*<<< orphan*/  phase; TYPE_1__ SCp; } ;
struct TYPE_13__ {TYPE_3__ scsi; TYPE_2__* host; struct scsi_cmnd* SCpnt; } ;
struct TYPE_11__ {int /*<<< orphan*/  host_no; } ;
typedef  TYPE_4__ AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  CMND_XFERINFO ; 
 int /*<<< orphan*/  PHASE_COMMAND ; 
 int /*<<< orphan*/  SBIC_TRANSCNTH ; 
 int /*<<< orphan*/  acornscsi_sbic_issuecmd (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ acornscsi_write_pio (TYPE_4__*,int /*<<< orphan*/ ,int*,scalar_t__,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbic_arm_write (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbic_arm_writenext (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static void
acornscsi_sendcommand(AS_Host *host)
{
	struct scsi_cmnd *SCpnt = host->SCpnt;

    sbic_arm_write(host, SBIC_TRANSCNTH, 0);
    sbic_arm_writenext(host, 0);
    sbic_arm_writenext(host, SCpnt->cmd_len - host->scsi.SCp.sent_command);

    acornscsi_sbic_issuecmd(host, CMND_XFERINFO);

    if (acornscsi_write_pio(host, SCpnt->cmnd,
	(int *)&host->scsi.SCp.sent_command, SCpnt->cmd_len, 1000000))
	printk("scsi%d: timeout while sending command\n", host->host->host_no);

    host->scsi.phase = PHASE_COMMAND;
}