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
typedef  int u32 ;
struct mmc_request {struct mmc_command* cmd; } ;
struct mmc_command {int flags; int* resp; int /*<<< orphan*/  error; } ;
struct au1xmmc_host {int flags; int /*<<< orphan*/  status; int /*<<< orphan*/  finish_task; scalar_t__ iobase; struct mmc_request* mrq; } ;

/* Variables and functions */
 int DMA_CHANNEL (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  EILSEQ ; 
 int HOST_F_DMA ; 
 int HOST_F_RECV ; 
 int HOST_F_XMIT ; 
 scalar_t__ HOST_STATUS (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_S_DATA ; 
 int /*<<< orphan*/  IRQ_OFF (struct au1xmmc_host*,int) ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 int SD_CONFIG_RA ; 
 int SD_CONFIG_RF ; 
 int SD_CONFIG_TH ; 
 scalar_t__ SD_RESP0 ; 
 scalar_t__ SD_RESP1 ; 
 scalar_t__ SD_RESP2 ; 
 scalar_t__ SD_RESP3 ; 
 int SD_STATUS_DB ; 
 int SD_STATUS_NE ; 
 int SD_STATUS_RC ; 
 int SD_STATUS_SC ; 
 int SD_STATUS_WC ; 
 int /*<<< orphan*/  au1xxx_dbdma_start (int) ; 
 void* au_readl (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void au1xmmc_cmd_complete(struct au1xmmc_host *host, u32 status)
{
	struct mmc_request *mrq = host->mrq;
	struct mmc_command *cmd;
	u32 r[4];
	int i, trans;

	if (!host->mrq)
		return;

	cmd = mrq->cmd;
	cmd->error = 0;

	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			r[0] = au_readl(host->iobase + SD_RESP3);
			r[1] = au_readl(host->iobase + SD_RESP2);
			r[2] = au_readl(host->iobase + SD_RESP1);
			r[3] = au_readl(host->iobase + SD_RESP0);

			/* The CRC is omitted from the response, so really
			 * we only got 120 bytes, but the engine expects
			 * 128 bits, so we have to shift things up.
			 */
			for (i = 0; i < 4; i++) {
				cmd->resp[i] = (r[i] & 0x00FFFFFF) << 8;
				if (i != 3)
					cmd->resp[i] |= (r[i + 1] & 0xFF000000) >> 24;
			}
		} else {
			/* Techincally, we should be getting all 48 bits of
			 * the response (SD_RESP1 + SD_RESP2), but because
			 * our response omits the CRC, our data ends up
			 * being shifted 8 bits to the right.  In this case,
			 * that means that the OSR data starts at bit 31,
			 * so we can just read RESP0 and return that.
			 */
			cmd->resp[0] = au_readl(host->iobase + SD_RESP0);
		}
	}

        /* Figure out errors */
	if (status & (SD_STATUS_SC | SD_STATUS_WC | SD_STATUS_RC))
		cmd->error = -EILSEQ;

	trans = host->flags & (HOST_F_XMIT | HOST_F_RECV);

	if (!trans || cmd->error) {
		IRQ_OFF(host, SD_CONFIG_TH | SD_CONFIG_RA | SD_CONFIG_RF);
		tasklet_schedule(&host->finish_task);
		return;
	}

	host->status = HOST_S_DATA;

	if (host->flags & HOST_F_DMA) {
#ifdef CONFIG_SOC_AU1200	/* DBDMA */
		u32 channel = DMA_CHANNEL(host);

		/* Start the DMA as soon as the buffer gets something in it */

		if (host->flags & HOST_F_RECV) {
			u32 mask = SD_STATUS_DB | SD_STATUS_NE;

			while((status & mask) != mask)
				status = au_readl(HOST_STATUS(host));
		}

		au1xxx_dbdma_start(channel);
#endif
	}
}