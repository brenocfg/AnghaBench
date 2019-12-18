#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  ASR_DBR ; 
 int /*<<< orphan*/  ASR_INT ; 
 int CMND_SBT ; 
 int CMND_XFERINFO ; 
 int /*<<< orphan*/  SBIC_DATA ; 
 int /*<<< orphan*/  SBIC_SSR ; 
 int /*<<< orphan*/  acornscsi_sbic_issuecmd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  acornscsi_sbic_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 unsigned char sbic_arm_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
unsigned char acornscsi_readmessagebyte(AS_Host *host)
{
    unsigned char message;

    acornscsi_sbic_issuecmd(host, CMND_XFERINFO | CMND_SBT);

    acornscsi_sbic_wait(host, ASR_DBR, ASR_DBR, 1000, "for message byte");

    message = sbic_arm_read(host, SBIC_DATA);

    /* wait for MSGIN-XFER-PAUSED */
    acornscsi_sbic_wait(host, ASR_INT, ASR_INT, 1000, "for interrupt after message byte");

    sbic_arm_read(host, SBIC_SSR);

    return message;
}