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
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {int /*<<< orphan*/  host_no; } ;
typedef  TYPE_2__ AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  SBIC_ASR ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*) ; 
 int sbic_arm_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
acornscsi_sbic_wait(AS_Host *host, int stat_mask, int stat, int timeout, char *msg)
{
	int asr;

	do {
		asr = sbic_arm_read(host, SBIC_ASR);

		if ((asr & stat_mask) == stat)
			return 0;

		udelay(1);
	} while (--timeout);

	printk("scsi%d: timeout while %s\n", host->host->host_no, msg);

	return -1;
}