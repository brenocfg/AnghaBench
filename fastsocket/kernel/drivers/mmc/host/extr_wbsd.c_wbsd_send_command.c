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
struct wbsd_host {int isr; scalar_t__ base; } ;
struct mmc_command {int opcode; int arg; int flags; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_CRC ; 
 int MMC_RSP_PRESENT ; 
 int WBSD_CARDTRAFFIC ; 
 scalar_t__ WBSD_CMDR ; 
 int /*<<< orphan*/  WBSD_IDX_STATUS ; 
 int WBSD_INT_CARD ; 
 int WBSD_INT_CRC ; 
 int WBSD_INT_TIMEOUT ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  wbsd_get_long_reply (struct wbsd_host*,struct mmc_command*) ; 
 int /*<<< orphan*/  wbsd_get_short_reply (struct wbsd_host*,struct mmc_command*) ; 
 int wbsd_read_index (struct wbsd_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wbsd_send_command(struct wbsd_host *host, struct mmc_command *cmd)
{
	int i;
	u8 status, isr;

	/*
	 * Clear accumulated ISR. The interrupt routine
	 * will fill this one with events that occur during
	 * transfer.
	 */
	host->isr = 0;

	/*
	 * Send the command (CRC calculated by host).
	 */
	outb(cmd->opcode, host->base + WBSD_CMDR);
	for (i = 3; i >= 0; i--)
		outb((cmd->arg >> (i * 8)) & 0xff, host->base + WBSD_CMDR);

	cmd->error = 0;

	/*
	 * Wait for the request to complete.
	 */
	do {
		status = wbsd_read_index(host, WBSD_IDX_STATUS);
	} while (status & WBSD_CARDTRAFFIC);

	/*
	 * Do we expect a reply?
	 */
	if (cmd->flags & MMC_RSP_PRESENT) {
		/*
		 * Read back status.
		 */
		isr = host->isr;

		/* Card removed? */
		if (isr & WBSD_INT_CARD)
			cmd->error = -ENOMEDIUM;
		/* Timeout? */
		else if (isr & WBSD_INT_TIMEOUT)
			cmd->error = -ETIMEDOUT;
		/* CRC? */
		else if ((cmd->flags & MMC_RSP_CRC) && (isr & WBSD_INT_CRC))
			cmd->error = -EILSEQ;
		/* All ok */
		else {
			if (cmd->flags & MMC_RSP_136)
				wbsd_get_long_reply(host, cmd);
			else
				wbsd_get_short_reply(host, cmd);
		}
	}
}