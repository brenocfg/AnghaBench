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
struct TYPE_2__ {unsigned long timeout_d; int /*<<< orphan*/  locality; scalar_t__ iobase; } ;
struct tpm_chip {TYPE_1__ vendor; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ TPM_STS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_TIMEOUT ; 
 int ioread8 (scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int get_burstcount(struct tpm_chip *chip)
{
	unsigned long stop;
	int burstcnt;

	/* wait for burstcount */
	/* which timeout value, spec has 2 answers (c & d) */
	stop = jiffies + chip->vendor.timeout_d;
	do {
		burstcnt = ioread8(chip->vendor.iobase +
				   TPM_STS(chip->vendor.locality) + 1);
		burstcnt += ioread8(chip->vendor.iobase +
				    TPM_STS(chip->vendor.locality) +
				    2) << 8;
		if (burstcnt)
			return burstcnt;
		msleep(TPM_TIMEOUT);
	} while (time_before(jiffies, stop));
	return -EBUSY;
}