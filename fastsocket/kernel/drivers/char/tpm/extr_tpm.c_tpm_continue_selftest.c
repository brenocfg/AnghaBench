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
typedef  int u8 ;
struct tpm_chip {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  tpm_transmit (struct tpm_chip*,int*,int) ; 

void tpm_continue_selftest(struct tpm_chip *chip)
{
	u8 data[] = {
		0, 193,			/* TPM_TAG_RQU_COMMAND */
		0, 0, 0, 10,		/* length */
		0, 0, 0, 83,		/* TPM_ORD_GetCapability */
	};

	tpm_transmit(chip, data, sizeof(data));
}