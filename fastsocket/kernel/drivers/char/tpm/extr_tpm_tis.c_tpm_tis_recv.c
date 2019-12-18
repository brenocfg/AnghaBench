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
struct TYPE_2__ {int /*<<< orphan*/  locality; int /*<<< orphan*/  int_queue; int /*<<< orphan*/  timeout_c; } ;
struct tpm_chip {TYPE_1__ vendor; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int ETIME ; 
 size_t TPM_HEADER_SIZE ; 
 int TPM_STS_DATA_AVAIL ; 
 int /*<<< orphan*/  TPM_STS_VALID ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int recv_data (struct tpm_chip*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  release_locality (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_tis_ready (struct tpm_chip*) ; 
 int tpm_tis_status (struct tpm_chip*) ; 
 int /*<<< orphan*/  wait_for_tpm_stat (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tpm_tis_recv(struct tpm_chip *chip, u8 *buf, size_t count)
{
	int size = 0;
	int expected, status;

	if (count < TPM_HEADER_SIZE) {
		size = -EIO;
		goto out;
	}

	/* read first 10 bytes, including tag, paramsize, and result */
	if ((size =
	     recv_data(chip, buf, TPM_HEADER_SIZE)) < TPM_HEADER_SIZE) {
		dev_err(chip->dev, "Unable to read header\n");
		goto out;
	}

	expected = be32_to_cpu(*(__be32 *) (buf + 2));
	if (expected > count) {
		size = -EIO;
		goto out;
	}

	if ((size +=
	     recv_data(chip, &buf[TPM_HEADER_SIZE],
		       expected - TPM_HEADER_SIZE)) < expected) {
		dev_err(chip->dev, "Unable to read remainder of result\n");
		size = -ETIME;
		goto out;
	}

	wait_for_tpm_stat(chip, TPM_STS_VALID, chip->vendor.timeout_c,
			  &chip->vendor.int_queue);
	status = tpm_tis_status(chip);
	if (status & TPM_STS_DATA_AVAIL) {	/* retry? */
		dev_err(chip->dev, "Error left over data\n");
		size = -EIO;
		goto out;
	}

out:
	tpm_tis_ready(chip);
	release_locality(chip, chip->vendor.locality, 0);
	return size;
}