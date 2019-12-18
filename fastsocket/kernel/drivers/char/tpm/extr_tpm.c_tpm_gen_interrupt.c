#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  subcap; int /*<<< orphan*/  subcap_size; int /*<<< orphan*/  cap; } ;
struct TYPE_6__ {TYPE_2__ getcap_in; } ;
struct TYPE_4__ {int /*<<< orphan*/  in; } ;
struct tpm_cmd_t {TYPE_3__ params; TYPE_1__ header; } ;
struct tpm_chip {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_CAP_PROP ; 
 int /*<<< orphan*/  TPM_CAP_PROP_TIS_TIMEOUT ; 
 int /*<<< orphan*/  TPM_INTERNAL_RESULT_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  tpm_getcap_header ; 
 int /*<<< orphan*/  transmit_cmd (struct tpm_chip*,struct tpm_cmd_t*,int /*<<< orphan*/ ,char*) ; 

void tpm_gen_interrupt(struct tpm_chip *chip)
{
	struct	tpm_cmd_t tpm_cmd;
	ssize_t rc;

	tpm_cmd.header.in = tpm_getcap_header;
	tpm_cmd.params.getcap_in.cap = TPM_CAP_PROP;
	tpm_cmd.params.getcap_in.subcap_size = cpu_to_be32(4);
	tpm_cmd.params.getcap_in.subcap = TPM_CAP_PROP_TIS_TIMEOUT;

	rc = transmit_cmd(chip, &tpm_cmd, TPM_INTERNAL_RESULT_SIZE,
			"attempting to determine the timeouts");
}