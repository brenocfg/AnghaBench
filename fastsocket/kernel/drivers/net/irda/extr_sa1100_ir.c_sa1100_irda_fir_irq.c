#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sa1100_irda {int hscr0; int /*<<< orphan*/  rxdma; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int HSCR0_HSSP ; 
 int HSSR0_EIF ; 
 int HSSR0_FRE ; 
 int HSSR0_RAB ; 
 int Ser2HSCR0 ; 
 int Ser2HSSR0 ; 
 struct sa1100_irda* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sa1100_irda_fir_error (struct sa1100_irda*,struct net_device*) ; 
 int /*<<< orphan*/  sa1100_irda_rx_dma_start (struct sa1100_irda*) ; 
 int /*<<< orphan*/  sa1100_stop_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sa1100_irda_fir_irq(struct net_device *dev)
{
	struct sa1100_irda *si = netdev_priv(dev);

	/*
	 * Stop RX DMA
	 */
	sa1100_stop_dma(si->rxdma);

	/*
	 * Framing error - we throw away the packet completely.
	 * Clearing RXE flushes the error conditions and data
	 * from the fifo.
	 */
	if (Ser2HSSR0 & (HSSR0_FRE | HSSR0_RAB)) {
		dev->stats.rx_errors++;

		if (Ser2HSSR0 & HSSR0_FRE)
			dev->stats.rx_frame_errors++;

		/*
		 * Clear out the DMA...
		 */
		Ser2HSCR0 = si->hscr0 | HSCR0_HSSP;

		/*
		 * Clear selected status bits now, so we
		 * don't miss them next time around.
		 */
		Ser2HSSR0 = HSSR0_FRE | HSSR0_RAB;
	}

	/*
	 * Deal with any receive errors.  The any of the lowest
	 * 8 bytes in the FIFO may contain an error.  We must read
	 * them one by one.  The "error" could even be the end of
	 * packet!
	 */
	if (Ser2HSSR0 & HSSR0_EIF)
		sa1100_irda_fir_error(si, dev);

	/*
	 * No matter what happens, we must restart reception.
	 */
	sa1100_irda_rx_dma_start(si);
}