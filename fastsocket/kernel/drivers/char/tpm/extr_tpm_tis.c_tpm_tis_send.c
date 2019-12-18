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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  locality; int /*<<< orphan*/  read_queue; scalar_t__ irq; scalar_t__ iobase; int /*<<< orphan*/  int_queue; int /*<<< orphan*/  timeout_c; int /*<<< orphan*/  timeout_b; } ;
struct tpm_chip {TYPE_1__ vendor; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ETIME ; 
 scalar_t__ TPM_DATA_FIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ TPM_STS (int /*<<< orphan*/ ) ; 
 int TPM_STS_COMMAND_READY ; 
 int TPM_STS_DATA_AVAIL ; 
 int TPM_STS_DATA_EXPECT ; 
 int /*<<< orphan*/  TPM_STS_GO ; 
 int TPM_STS_VALID ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int get_burstcount (struct tpm_chip*) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  itpm ; 
 int /*<<< orphan*/  release_locality (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_locality (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_calc_ordinal_duration (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_tis_ready (struct tpm_chip*) ; 
 int tpm_tis_status (struct tpm_chip*) ; 
 scalar_t__ wait_for_tpm_stat (struct tpm_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tpm_tis_send(struct tpm_chip *chip, u8 *buf, size_t len)
{
	int rc, status, burstcnt;
	size_t count = 0;
	u32 ordinal;

	if (request_locality(chip, 0) < 0)
		return -EBUSY;

	status = tpm_tis_status(chip);
	if ((status & TPM_STS_COMMAND_READY) == 0) {
		tpm_tis_ready(chip);
		if (wait_for_tpm_stat
		    (chip, TPM_STS_COMMAND_READY, chip->vendor.timeout_b,
		     &chip->vendor.int_queue) < 0) {
			rc = -ETIME;
			goto out_err;
		}
	}

	while (count < len - 1) {
		burstcnt = get_burstcount(chip);
		for (; burstcnt > 0 && count < len - 1; burstcnt--) {
			iowrite8(buf[count], chip->vendor.iobase +
				 TPM_DATA_FIFO(chip->vendor.locality));
			count++;
		}

		wait_for_tpm_stat(chip, TPM_STS_VALID, chip->vendor.timeout_c,
				  &chip->vendor.int_queue);
		status = tpm_tis_status(chip);
		if (!itpm && (status & TPM_STS_DATA_EXPECT) == 0) {
			rc = -EIO;
			goto out_err;
		}
	}

	/* write last byte */
	iowrite8(buf[count],
		 chip->vendor.iobase + TPM_DATA_FIFO(chip->vendor.locality));
	wait_for_tpm_stat(chip, TPM_STS_VALID, chip->vendor.timeout_c,
			  &chip->vendor.int_queue);
	status = tpm_tis_status(chip);
	if ((status & TPM_STS_DATA_EXPECT) != 0) {
		rc = -EIO;
		goto out_err;
	}

	/* go and do it */
	iowrite8(TPM_STS_GO,
		 chip->vendor.iobase + TPM_STS(chip->vendor.locality));

	if (chip->vendor.irq) {
		ordinal = be32_to_cpu(*((__be32 *) (buf + 6)));
		if (wait_for_tpm_stat
		    (chip, TPM_STS_DATA_AVAIL | TPM_STS_VALID,
		     tpm_calc_ordinal_duration(chip, ordinal),
		     &chip->vendor.read_queue) < 0) {
			rc = -ETIME;
			goto out_err;
		}
	}
	return len;
out_err:
	tpm_tis_ready(chip);
	release_locality(chip, chip->vendor.locality, 0);
	return rc;
}