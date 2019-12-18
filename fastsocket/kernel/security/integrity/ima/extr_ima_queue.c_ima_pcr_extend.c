#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IMA_MEASURE_PCR_IDX ; 
 int /*<<< orphan*/  TPM_ANY_NUM ; 
 int /*<<< orphan*/  ima_used_chip ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int tpm_pcr_extend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int ima_pcr_extend(const u8 *hash)
{
	int result = 0;

	if (!ima_used_chip)
		return result;

	result = tpm_pcr_extend(TPM_ANY_NUM, CONFIG_IMA_MEASURE_PCR_IDX, hash);
	if (result != 0)
		pr_err("IMA: Error Communicating to TPM chip\n");
	return result;
}