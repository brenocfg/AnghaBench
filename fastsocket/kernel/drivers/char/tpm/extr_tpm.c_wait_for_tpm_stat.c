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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
typedef  int u8 ;
struct TYPE_2__ {int (* status ) (struct tpm_chip*) ;scalar_t__ irq; } ;
struct tpm_chip {TYPE_1__ vendor; } ;

/* Variables and functions */
 long ERESTARTSYS ; 
 int ETIME ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  TPM_TIMEOUT ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ freezing (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int stub1 (struct tpm_chip*) ; 
 int stub2 (struct tpm_chip*) ; 
 int stub3 (struct tpm_chip*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

int wait_for_tpm_stat(struct tpm_chip *chip, u8 mask, unsigned long timeout,
			 wait_queue_head_t *queue)
{
	unsigned long stop;
	long rc;
	u8 status;

	/* check current status */
	status = chip->vendor.status(chip);
	if ((status & mask) == mask)
		return 0;

	stop = jiffies + timeout;

	if (chip->vendor.irq) {
again:
		timeout = stop - jiffies;
		if ((long)timeout <= 0)
			return -ETIME;
		rc = wait_event_interruptible_timeout(*queue,
						      ((chip->vendor.status(chip)
						      & mask) == mask),
						      timeout);
		if (rc > 0)
			return 0;
		if (rc == -ERESTARTSYS && freezing(current)) {
			clear_thread_flag(TIF_SIGPENDING);
			goto again;
		}
	} else {
		do {
			msleep(TPM_TIMEOUT);
			status = chip->vendor.status(chip);
			if ((status & mask) == mask)
				return 0;
		} while (time_before(jiffies, stop));
	}
	return -ETIME;
}