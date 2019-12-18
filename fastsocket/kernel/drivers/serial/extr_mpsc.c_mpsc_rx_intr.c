#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct tty_struct {scalar_t__ low_latency; } ;
struct mpsc_rx_desc {int /*<<< orphan*/  cmdstat; int /*<<< orphan*/  bytecnt; } ;
struct TYPE_8__ {scalar_t__ rx; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  brk; } ;
struct TYPE_9__ {scalar_t__ read_status_mask; scalar_t__ ignore_status_mask; int /*<<< orphan*/  dev; TYPE_3__ icount; int /*<<< orphan*/  line; TYPE_2__* state; } ;
struct mpsc_port_info {int rxr_posn; scalar_t__ sdma_base; scalar_t__ cache_mgmt; TYPE_4__ port; scalar_t__ rxr; int /*<<< orphan*/ * rxb; } ;
struct TYPE_6__ {struct tty_struct* tty; } ;
struct TYPE_7__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int MPSC_RXBE_SIZE ; 
 int MPSC_RXRE_SIZE ; 
 int MPSC_RXR_ENTRIES ; 
 scalar_t__ SDMA_DESC_CMDSTAT_BR ; 
 scalar_t__ SDMA_DESC_CMDSTAT_EI ; 
 scalar_t__ SDMA_DESC_CMDSTAT_F ; 
 scalar_t__ SDMA_DESC_CMDSTAT_FR ; 
 scalar_t__ SDMA_DESC_CMDSTAT_L ; 
 scalar_t__ SDMA_DESC_CMDSTAT_O ; 
 scalar_t__ SDMA_DESC_CMDSTAT_OR ; 
 scalar_t__ SDMA_DESC_CMDSTAT_PE ; 
 scalar_t__ SDMA_SDCM ; 
 int SDMA_SDCM_ERD ; 
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 char TTY_PARITY ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  dma_cache_sync (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  invalidate_dcache_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mpsc_start_rx (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 scalar_t__ serial_polled ; 
 scalar_t__ tty_buffer_request_room (struct tty_struct*,scalar_t__) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,int /*<<< orphan*/ ,char) ; 
 scalar_t__ uart_handle_break (TYPE_4__*) ; 
 scalar_t__ uart_handle_sysrq_char (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int mpsc_rx_intr(struct mpsc_port_info *pi)
{
	struct mpsc_rx_desc *rxre;
	struct tty_struct *tty = pi->port.state->port.tty;
	u32	cmdstat, bytes_in, i;
	int	rc = 0;
	u8	*bp;
	char	flag = TTY_NORMAL;

	pr_debug("mpsc_rx_intr[%d]: Handling Rx intr\n", pi->port.line);

	rxre = (struct mpsc_rx_desc *)(pi->rxr + (pi->rxr_posn*MPSC_RXRE_SIZE));

	dma_cache_sync(pi->port.dev, (void *)rxre, MPSC_RXRE_SIZE,
			DMA_FROM_DEVICE);
#if defined(CONFIG_PPC32) && !defined(CONFIG_NOT_COHERENT_CACHE)
	if (pi->cache_mgmt) /* GT642[46]0 Res #COMM-2 */
		invalidate_dcache_range((ulong)rxre,
				(ulong)rxre + MPSC_RXRE_SIZE);
#endif

	/*
	 * Loop through Rx descriptors handling ones that have been completed.
	 */
	while (!((cmdstat = be32_to_cpu(rxre->cmdstat))
				& SDMA_DESC_CMDSTAT_O)) {
		bytes_in = be16_to_cpu(rxre->bytecnt);
#ifdef CONFIG_CONSOLE_POLL
		if (unlikely(serial_polled)) {
			serial_polled = 0;
			return 0;
		}
#endif
		/* Following use of tty struct directly is deprecated */
		if (unlikely(tty_buffer_request_room(tty, bytes_in)
					< bytes_in)) {
			if (tty->low_latency)
				tty_flip_buffer_push(tty);
			/*
			 * If this failed then we will throw away the bytes
			 * but must do so to clear interrupts.
			 */
		}

		bp = pi->rxb + (pi->rxr_posn * MPSC_RXBE_SIZE);
		dma_cache_sync(pi->port.dev, (void *)bp, MPSC_RXBE_SIZE,
				DMA_FROM_DEVICE);
#if defined(CONFIG_PPC32) && !defined(CONFIG_NOT_COHERENT_CACHE)
		if (pi->cache_mgmt) /* GT642[46]0 Res #COMM-2 */
			invalidate_dcache_range((ulong)bp,
					(ulong)bp + MPSC_RXBE_SIZE);
#endif

		/*
		 * Other than for parity error, the manual provides little
		 * info on what data will be in a frame flagged by any of
		 * these errors.  For parity error, it is the last byte in
		 * the buffer that had the error.  As for the rest, I guess
		 * we'll assume there is no data in the buffer.
		 * If there is...it gets lost.
		 */
		if (unlikely(cmdstat & (SDMA_DESC_CMDSTAT_BR
						| SDMA_DESC_CMDSTAT_FR
						| SDMA_DESC_CMDSTAT_OR))) {

			pi->port.icount.rx++;

			if (cmdstat & SDMA_DESC_CMDSTAT_BR) {	/* Break */
				pi->port.icount.brk++;

				if (uart_handle_break(&pi->port))
					goto next_frame;
			} else if (cmdstat & SDMA_DESC_CMDSTAT_FR) {
				pi->port.icount.frame++;
			} else if (cmdstat & SDMA_DESC_CMDSTAT_OR) {
				pi->port.icount.overrun++;
			}

			cmdstat &= pi->port.read_status_mask;

			if (cmdstat & SDMA_DESC_CMDSTAT_BR)
				flag = TTY_BREAK;
			else if (cmdstat & SDMA_DESC_CMDSTAT_FR)
				flag = TTY_FRAME;
			else if (cmdstat & SDMA_DESC_CMDSTAT_OR)
				flag = TTY_OVERRUN;
			else if (cmdstat & SDMA_DESC_CMDSTAT_PE)
				flag = TTY_PARITY;
		}

		if (uart_handle_sysrq_char(&pi->port, *bp)) {
			bp++;
			bytes_in--;
#ifdef CONFIG_CONSOLE_POLL
			if (unlikely(serial_polled)) {
				serial_polled = 0;
				return 0;
			}
#endif
			goto next_frame;
		}

		if ((unlikely(cmdstat & (SDMA_DESC_CMDSTAT_BR
						| SDMA_DESC_CMDSTAT_FR
						| SDMA_DESC_CMDSTAT_OR)))
				&& !(cmdstat & pi->port.ignore_status_mask)) {
			tty_insert_flip_char(tty, *bp, flag);
		} else {
			for (i=0; i<bytes_in; i++)
				tty_insert_flip_char(tty, *bp++, TTY_NORMAL);

			pi->port.icount.rx += bytes_in;
		}

next_frame:
		rxre->bytecnt = cpu_to_be16(0);
		wmb();
		rxre->cmdstat = cpu_to_be32(SDMA_DESC_CMDSTAT_O
				| SDMA_DESC_CMDSTAT_EI | SDMA_DESC_CMDSTAT_F
				| SDMA_DESC_CMDSTAT_L);
		wmb();
		dma_cache_sync(pi->port.dev, (void *)rxre, MPSC_RXRE_SIZE,
				DMA_BIDIRECTIONAL);
#if defined(CONFIG_PPC32) && !defined(CONFIG_NOT_COHERENT_CACHE)
		if (pi->cache_mgmt) /* GT642[46]0 Res #COMM-2 */
			flush_dcache_range((ulong)rxre,
					(ulong)rxre + MPSC_RXRE_SIZE);
#endif

		/* Advance to next descriptor */
		pi->rxr_posn = (pi->rxr_posn + 1) & (MPSC_RXR_ENTRIES - 1);
		rxre = (struct mpsc_rx_desc *)
			(pi->rxr + (pi->rxr_posn * MPSC_RXRE_SIZE));
		dma_cache_sync(pi->port.dev, (void *)rxre, MPSC_RXRE_SIZE,
				DMA_FROM_DEVICE);
#if defined(CONFIG_PPC32) && !defined(CONFIG_NOT_COHERENT_CACHE)
		if (pi->cache_mgmt) /* GT642[46]0 Res #COMM-2 */
			invalidate_dcache_range((ulong)rxre,
					(ulong)rxre + MPSC_RXRE_SIZE);
#endif
		rc = 1;
	}

	/* Restart rx engine, if its stopped */
	if ((readl(pi->sdma_base + SDMA_SDCM) & SDMA_SDCM_ERD) == 0)
		mpsc_start_rx(pi);

	tty_flip_buffer_push(tty);
	return rc;
}