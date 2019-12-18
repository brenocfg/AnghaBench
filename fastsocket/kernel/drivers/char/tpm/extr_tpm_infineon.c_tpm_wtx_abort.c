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
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TPM_CTRL_WTX_ABORT ; 
 int TPM_VL_VER ; 
 int /*<<< orphan*/  TPM_WTX_MSLEEP_TIME ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ number_of_wtx ; 
 int /*<<< orphan*/  wait_and_send (struct tpm_chip*,int) ; 

__attribute__((used)) static void tpm_wtx_abort(struct tpm_chip *chip)
{
	dev_info(chip->dev, "Aborting WTX\n");
	wait_and_send(chip, TPM_VL_VER);
	wait_and_send(chip, TPM_CTRL_WTX_ABORT);
	wait_and_send(chip, 0x00);
	wait_and_send(chip, 0x00);
	number_of_wtx = 0;
	msleep(TPM_WTX_MSLEEP_TIME);
}