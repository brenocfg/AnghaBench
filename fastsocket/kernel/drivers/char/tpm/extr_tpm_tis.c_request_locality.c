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
struct TYPE_2__ {unsigned long timeout_a; int /*<<< orphan*/  int_queue; scalar_t__ irq; scalar_t__ iobase; } ;
struct tpm_chip {TYPE_1__ vendor; } ;

/* Variables and functions */
 scalar_t__ TPM_ACCESS (int) ; 
 int /*<<< orphan*/  TPM_ACCESS_REQUEST_USE ; 
 int /*<<< orphan*/  TPM_TIMEOUT ; 
 scalar_t__ check_locality (struct tpm_chip*,int) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int request_locality(struct tpm_chip *chip, int l)
{
	unsigned long stop;
	long rc;

	if (check_locality(chip, l) >= 0)
		return l;

	iowrite8(TPM_ACCESS_REQUEST_USE,
		 chip->vendor.iobase + TPM_ACCESS(l));

	if (chip->vendor.irq) {
		rc = wait_event_interruptible_timeout(chip->vendor.int_queue,
						      (check_locality
						       (chip, l) >= 0),
						      chip->vendor.timeout_a);
		if (rc > 0)
			return l;

	} else {
		/* wait for burstcount */
		stop = jiffies + chip->vendor.timeout_a;
		do {
			if (check_locality(chip, l) >= 0)
				return l;
			msleep(TPM_TIMEOUT);
		}
		while (time_before(jiffies, stop));
	}
	return -1;
}