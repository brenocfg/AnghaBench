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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_host {int dummy; } ;
struct mmc_command {int arg; int /*<<< orphan*/ * resp; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_RSP_SPI_R3 ; 
 int /*<<< orphan*/  MMC_SPI_READ_OCR ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int mmc_wait_for_cmd (struct mmc_host*,struct mmc_command*,int /*<<< orphan*/ ) ; 

int mmc_spi_read_ocr(struct mmc_host *host, int highcap, u32 *ocrp)
{
	struct mmc_command cmd;
	int err;

	memset(&cmd, 0, sizeof(struct mmc_command));

	cmd.opcode = MMC_SPI_READ_OCR;
	cmd.arg = highcap ? (1 << 30) : 0;
	cmd.flags = MMC_RSP_SPI_R3;

	err = mmc_wait_for_cmd(host, &cmd, 0);

	*ocrp = cmd.resp[1];
	return err;
}