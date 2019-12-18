#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u32 ;
struct spi_transfer {int len; int cs_change; int /*<<< orphan*/  rx_dma; int /*<<< orphan*/  tx_dma; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct scratch {void** status; } ;
struct TYPE_8__ {int is_dma_mapped; } ;
struct mmc_spi_host {TYPE_2__* spi; int /*<<< orphan*/  data_dma; scalar_t__ dma_dev; TYPE_3__ m; struct spi_transfer t; struct scratch* data; } ;
struct mmc_request {TYPE_1__* data; } ;
struct mmc_command {int arg; int opcode; int flags; int error; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int MMC_DATA_READ ; 
 int MMC_RSP_BUSY ; 
 int MMC_RSP_SPI_B4 ; 
 int MMC_RSP_SPI_S2 ; 
 int crc7 (int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maptype (struct mmc_command*) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int,int) ; 
 int mmc_spi_response_get (struct mmc_spi_host*,struct mmc_command*,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,TYPE_3__*) ; 
 int /*<<< orphan*/  spi_message_init (TYPE_3__*) ; 
 int spi_sync (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int
mmc_spi_command_send(struct mmc_spi_host *host,
		struct mmc_request *mrq,
		struct mmc_command *cmd, int cs_on)
{
	struct scratch		*data = host->data;
	u8			*cp = data->status;
	u32			arg = cmd->arg;
	int			status;
	struct spi_transfer	*t;

	/* We can handle most commands (except block reads) in one full
	 * duplex I/O operation before either starting the next transfer
	 * (data block or command) or else deselecting the card.
	 *
	 * First, write 7 bytes:
	 *  - an all-ones byte to ensure the card is ready
	 *  - opcode byte (plus start and transmission bits)
	 *  - four bytes of big-endian argument
	 *  - crc7 (plus end bit) ... always computed, it's cheap
	 *
	 * We init the whole buffer to all-ones, which is what we need
	 * to write while we're reading (later) response data.
	 */
	memset(cp++, 0xff, sizeof(data->status));

	*cp++ = 0x40 | cmd->opcode;
	*cp++ = (u8)(arg >> 24);
	*cp++ = (u8)(arg >> 16);
	*cp++ = (u8)(arg >> 8);
	*cp++ = (u8)arg;
	*cp++ = (crc7(0, &data->status[1], 5) << 1) | 0x01;

	/* Then, read up to 13 bytes (while writing all-ones):
	 *  - N(CR) (== 1..8) bytes of all-ones
	 *  - status byte (for all response types)
	 *  - the rest of the response, either:
	 *      + nothing, for R1 or R1B responses
	 *	+ second status byte, for R2 responses
	 *	+ four data bytes, for R3 and R7 responses
	 *
	 * Finally, read some more bytes ... in the nice cases we know in
	 * advance how many, and reading 1 more is always OK:
	 *  - N(EC) (== 0..N) bytes of all-ones, before deselect/finish
	 *  - N(RC) (== 1..N) bytes of all-ones, before next command
	 *  - N(WR) (== 1..N) bytes of all-ones, before data write
	 *
	 * So in those cases one full duplex I/O of at most 21 bytes will
	 * handle the whole command, leaving the card ready to receive a
	 * data block or new command.  We do that whenever we can, shaving
	 * CPU and IRQ costs (especially when using DMA or FIFOs).
	 *
	 * There are two other cases, where it's not generally practical
	 * to rely on a single I/O:
	 *
	 *  - R1B responses need at least N(EC) bytes of all-zeroes.
	 *
	 *    In this case we can *try* to fit it into one I/O, then
	 *    maybe read more data later.
	 *
	 *  - Data block reads are more troublesome, since a variable
	 *    number of padding bytes precede the token and data.
	 *      + N(CX) (== 0..8) bytes of all-ones, before CSD or CID
	 *      + N(AC) (== 1..many) bytes of all-ones
	 *
	 *    In this case we currently only have minimal speedups here:
	 *    when N(CR) == 1 we can avoid I/O in response_get().
	 */
	if (cs_on && (mrq->data->flags & MMC_DATA_READ)) {
		cp += 2;	/* min(N(CR)) + status */
		/* R1 */
	} else {
		cp += 10;	/* max(N(CR)) + status + min(N(RC),N(WR)) */
		if (cmd->flags & MMC_RSP_SPI_S2)	/* R2/R5 */
			cp++;
		else if (cmd->flags & MMC_RSP_SPI_B4)	/* R3/R4/R7 */
			cp += 4;
		else if (cmd->flags & MMC_RSP_BUSY)	/* R1B */
			cp = data->status + sizeof(data->status);
		/* else:  R1 (most commands) */
	}

	dev_dbg(&host->spi->dev, "  mmc_spi: CMD%d, resp %s\n",
		cmd->opcode, maptype(cmd));

	/* send command, leaving chipselect active */
	spi_message_init(&host->m);

	t = &host->t;
	memset(t, 0, sizeof(*t));
	t->tx_buf = t->rx_buf = data->status;
	t->tx_dma = t->rx_dma = host->data_dma;
	t->len = cp - data->status;
	t->cs_change = 1;
	spi_message_add_tail(t, &host->m);

	if (host->dma_dev) {
		host->m.is_dma_mapped = 1;
		dma_sync_single_for_device(host->dma_dev,
				host->data_dma, sizeof(*host->data),
				DMA_BIDIRECTIONAL);
	}
	status = spi_sync(host->spi, &host->m);

	if (host->dma_dev)
		dma_sync_single_for_cpu(host->dma_dev,
				host->data_dma, sizeof(*host->data),
				DMA_BIDIRECTIONAL);
	if (status < 0) {
		dev_dbg(&host->spi->dev, "  ... write returned %d\n", status);
		cmd->error = status;
		return status;
	}

	/* after no-data commands and STOP_TRANSMISSION, chipselect off */
	return mmc_spi_response_get(host, cmd, cs_on);
}