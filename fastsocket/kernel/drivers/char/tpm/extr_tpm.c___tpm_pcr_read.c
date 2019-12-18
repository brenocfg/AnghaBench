#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/  pcr_result; } ;
struct TYPE_6__ {int /*<<< orphan*/  pcr_idx; } ;
struct TYPE_8__ {TYPE_3__ pcrread_out; TYPE_2__ pcrread_in; } ;
struct TYPE_5__ {int /*<<< orphan*/  in; } ;
struct tpm_cmd_t {TYPE_4__ params; TYPE_1__ header; } ;
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_PCR_RESULT_SIZE ; 
 int /*<<< orphan*/  TPM_DIGEST_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcrread_header ; 
 int transmit_cmd (struct tpm_chip*,struct tpm_cmd_t*,int /*<<< orphan*/ ,char*) ; 

int __tpm_pcr_read(struct tpm_chip *chip, int pcr_idx, u8 *res_buf)
{
	int rc;
	struct tpm_cmd_t cmd;

	cmd.header.in = pcrread_header;
	cmd.params.pcrread_in.pcr_idx = cpu_to_be32(pcr_idx);
	rc = transmit_cmd(chip, &cmd, READ_PCR_RESULT_SIZE,
			  "attempting to read a pcr value");

	if (rc == 0)
		memcpy(res_buf, cmd.params.pcrread_out.pcr_result,
		       TPM_DIGEST_SIZE);
	return rc;
}