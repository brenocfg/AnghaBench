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
typedef  int u8 ;
typedef  size_t u32 ;
struct TYPE_2__ {int (* status ) (struct tpm_chip*) ;int req_complete_mask; int req_complete_val; int req_canceled; int /*<<< orphan*/  (* recv ) (struct tpm_chip*,int*,size_t) ;int /*<<< orphan*/  (* cancel ) (struct tpm_chip*) ;scalar_t__ irq; int /*<<< orphan*/  (* send ) (struct tpm_chip*,int*,size_t) ;} ;
struct tpm_chip {int /*<<< orphan*/  tpm_mutex; int /*<<< orphan*/  dev; TYPE_1__ vendor; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  ECANCELED ; 
 int /*<<< orphan*/  ENODATA ; 
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  TPM_TIMEOUT ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  stub1 (struct tpm_chip*,int*,size_t) ; 
 int stub2 (struct tpm_chip*) ; 
 int /*<<< orphan*/  stub3 (struct tpm_chip*) ; 
 int /*<<< orphan*/  stub4 (struct tpm_chip*,int*,size_t) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 unsigned long tpm_calc_ordinal_duration (struct tpm_chip*,size_t) ; 

__attribute__((used)) static ssize_t tpm_transmit(struct tpm_chip *chip, const char *buf,
			    size_t bufsiz)
{
	ssize_t rc;
	u32 count, ordinal;
	unsigned long stop;

	count = be32_to_cpu(*((__be32 *) (buf + 2)));
	ordinal = be32_to_cpu(*((__be32 *) (buf + 6)));
	if (count == 0)
		return -ENODATA;
	if (count > bufsiz) {
		dev_err(chip->dev,
			"invalid count value %x %zx \n", count, bufsiz);
		return -E2BIG;
	}

	mutex_lock(&chip->tpm_mutex);

	if ((rc = chip->vendor.send(chip, (u8 *) buf, count)) < 0) {
		dev_err(chip->dev,
			"tpm_transmit: tpm_send: error %zd\n", rc);
		goto out;
	}

	if (chip->vendor.irq)
		goto out_recv;

	stop = jiffies + tpm_calc_ordinal_duration(chip, ordinal);
	do {
		u8 status = chip->vendor.status(chip);
		if ((status & chip->vendor.req_complete_mask) ==
		    chip->vendor.req_complete_val)
			goto out_recv;

		if ((status == chip->vendor.req_canceled)) {
			dev_err(chip->dev, "Operation Canceled\n");
			rc = -ECANCELED;
			goto out;
		}

		msleep(TPM_TIMEOUT);	/* CHECK */
		rmb();
	} while (time_before(jiffies, stop));

	chip->vendor.cancel(chip);
	dev_err(chip->dev, "Operation Timed out\n");
	rc = -ETIME;
	goto out;

out_recv:
	rc = chip->vendor.recv(chip, (u8 *) buf, bufsiz);
	if (rc < 0)
		dev_err(chip->dev,
			"tpm_transmit: tpm_recv: error %zd\n", rc);
out:
	mutex_unlock(&chip->tpm_mutex);
	return rc;
}