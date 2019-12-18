#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Status; } ;
struct TYPE_9__ {TYPE_1__ SCp; } ;
struct TYPE_10__ {TYPE_2__ scsi; } ;
typedef  TYPE_3__ AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  ASR_DBR ; 
 int CMND_SBT ; 
 int CMND_XFERINFO ; 
 int /*<<< orphan*/  SBIC_DATA ; 
 int /*<<< orphan*/  acornscsi_sbic_issuecmd (TYPE_3__*,int) ; 
 int /*<<< orphan*/  acornscsi_sbic_wait (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  sbic_arm_read (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void acornscsi_readstatusbyte(AS_Host *host)
{
    acornscsi_sbic_issuecmd(host, CMND_XFERINFO|CMND_SBT);
    acornscsi_sbic_wait(host, ASR_DBR, ASR_DBR, 1000, "reading status byte");
    host->scsi.SCp.Status = sbic_arm_read(host, SBIC_DATA);
}