#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ base; } ;
struct tpm_chip {int /*<<< orphan*/  dev; TYPE_1__ vendor; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ NSC_DATA ; 
 scalar_t__ NSC_STATUS ; 
 int NSC_STATUS_OBF ; 
 int NSC_STATUS_RDY ; 
 int /*<<< orphan*/  TPM_TIMEOUT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int inb (scalar_t__) ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int nsc_wait_for_ready(struct tpm_chip *chip)
{
	int status;
	unsigned long stop;

	/* status immediately available check */
	status = inb(chip->vendor.base + NSC_STATUS);
	if (status & NSC_STATUS_OBF)
		status = inb(chip->vendor.base + NSC_DATA);
	if (status & NSC_STATUS_RDY)
		return 0;

	/* wait for status */
	stop = jiffies + 100;
	do {
		msleep(TPM_TIMEOUT);
		status = inb(chip->vendor.base + NSC_STATUS);
		if (status & NSC_STATUS_OBF)
			status = inb(chip->vendor.base + NSC_DATA);
		if (status & NSC_STATUS_RDY)
			return 0;
	}
	while (time_before(jiffies, stop));

	dev_info(chip->dev, "wait for ready failed\n");
	return -EBUSY;
}