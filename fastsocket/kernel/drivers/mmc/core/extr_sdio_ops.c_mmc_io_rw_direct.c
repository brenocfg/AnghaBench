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
struct mmc_command {int arg; int flags; int* resp; int /*<<< orphan*/  opcode; } ;
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ERANGE ; 
 int MMC_CMD_AC ; 
 int MMC_RSP_R5 ; 
 int MMC_RSP_SPI_R5 ; 
 int R5_ERROR ; 
 int R5_FUNCTION_NUMBER ; 
 int R5_OUT_OF_RANGE ; 
 int /*<<< orphan*/  SD_IO_RW_DIRECT ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmc_host_is_spi (int /*<<< orphan*/ ) ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,struct mmc_command*,int /*<<< orphan*/ ) ; 

int mmc_io_rw_direct(struct mmc_card *card, int write, unsigned fn,
	unsigned addr, u8 in, u8* out)
{
	struct mmc_command cmd;
	int err;

	BUG_ON(!card);
	BUG_ON(fn > 7);

	/* sanity check */
	if (addr & ~0x1FFFF)
		return -EINVAL;

	memset(&cmd, 0, sizeof(struct mmc_command));

	cmd.opcode = SD_IO_RW_DIRECT;
	cmd.arg = write ? 0x80000000 : 0x00000000;
	cmd.arg |= fn << 28;
	cmd.arg |= (write && out) ? 0x08000000 : 0x00000000;
	cmd.arg |= addr << 9;
	cmd.arg |= in;
	cmd.flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_AC;

	err = mmc_wait_for_cmd(card->host, &cmd, 0);
	if (err)
		return err;

	if (mmc_host_is_spi(card->host)) {
		/* host driver already reported errors */
	} else {
		if (cmd.resp[0] & R5_ERROR)
			return -EIO;
		if (cmd.resp[0] & R5_FUNCTION_NUMBER)
			return -EINVAL;
		if (cmd.resp[0] & R5_OUT_OF_RANGE)
			return -ERANGE;
	}

	if (out) {
		if (mmc_host_is_spi(card->host))
			*out = (cmd.resp[0] >> 8) & 0xFF;
		else
			*out = cmd.resp[0] & 0xFF;
	}

	return 0;
}