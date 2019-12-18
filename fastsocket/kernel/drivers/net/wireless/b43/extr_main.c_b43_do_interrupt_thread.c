#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  rx_ring; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  txerr_cnt; } ;
struct b43_wldev {int* dma_reason; int irq_reason; int use_pio; int* irq_bit_count; int /*<<< orphan*/  irq_count; int /*<<< orphan*/  irq_mask; TYPE_3__ dma; TYPE_2__ pio; int /*<<< orphan*/  wl; TYPE_1__ phy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  B43_DBG_VERBOSESTATS ; 
 scalar_t__ B43_DEBUG ; 
 int B43_DMAIRQ_FATALMASK ; 
 int B43_DMAIRQ_RDESC_UFLOW ; 
 int B43_DMAIRQ_RX_DONE ; 
 int B43_IRQ_ATIM_END ; 
 int B43_IRQ_BEACON ; 
 int B43_IRQ_MAC_TXERR ; 
 int B43_IRQ_NOISESAMPLE_OK ; 
 int B43_IRQ_PHY_TXERR ; 
 int B43_IRQ_PMQ ; 
 int B43_IRQ_TBTT_INDI ; 
 int B43_IRQ_TXFIFO_FLUSH_OK ; 
 int B43_IRQ_TX_OK ; 
 int B43_IRQ_UCODE_DEBUG ; 
 int /*<<< orphan*/  B43_MMIO_GEN_IRQ_MASK ; 
 int /*<<< orphan*/  B43_PHY_TX_BADNESS_LIMIT ; 
 scalar_t__ B43_STAT_STARTED ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_controller_restart (struct b43_wldev*,char*) ; 
 scalar_t__ b43_debug (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_dma_handle_rx_overflow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_dma_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_pio_rx (int /*<<< orphan*/ ) ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 
 scalar_t__ b43_using_pio_transfers (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  b43warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  handle_irq_atim_end (struct b43_wldev*) ; 
 int /*<<< orphan*/  handle_irq_beacon (struct b43_wldev*) ; 
 int /*<<< orphan*/  handle_irq_noise (struct b43_wldev*) ; 
 int /*<<< orphan*/  handle_irq_pmq (struct b43_wldev*) ; 
 int /*<<< orphan*/  handle_irq_tbtt_indication (struct b43_wldev*) ; 
 int /*<<< orphan*/  handle_irq_transmit_status (struct b43_wldev*) ; 
 int /*<<< orphan*/  handle_irq_ucode_debug (struct b43_wldev*) ; 
 int /*<<< orphan*/  rmb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void b43_do_interrupt_thread(struct b43_wldev *dev)
{
	u32 reason;
	u32 dma_reason[ARRAY_SIZE(dev->dma_reason)];
	u32 merged_dma_reason = 0;
	int i;

	if (unlikely(b43_status(dev) != B43_STAT_STARTED))
		return;

	reason = dev->irq_reason;
	for (i = 0; i < ARRAY_SIZE(dma_reason); i++) {
		dma_reason[i] = dev->dma_reason[i];
		merged_dma_reason |= dma_reason[i];
	}

	if (unlikely(reason & B43_IRQ_MAC_TXERR))
		b43err(dev->wl, "MAC transmission error\n");

	if (unlikely(reason & B43_IRQ_PHY_TXERR)) {
		b43err(dev->wl, "PHY transmission error\n");
		rmb();
		if (unlikely(atomic_dec_and_test(&dev->phy.txerr_cnt))) {
			atomic_set(&dev->phy.txerr_cnt,
				   B43_PHY_TX_BADNESS_LIMIT);
			b43err(dev->wl, "Too many PHY TX errors, "
					"restarting the controller\n");
			b43_controller_restart(dev, "PHY TX errors");
		}
	}

	if (unlikely(merged_dma_reason & (B43_DMAIRQ_FATALMASK))) {
		b43err(dev->wl,
			"Fatal DMA error: 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X\n",
			dma_reason[0], dma_reason[1],
			dma_reason[2], dma_reason[3],
			dma_reason[4], dma_reason[5]);
		b43err(dev->wl, "This device does not support DMA "
			       "on your system. It will now be switched to PIO.\n");
		/* Fall back to PIO transfers if we get fatal DMA errors! */
		dev->use_pio = true;
		b43_controller_restart(dev, "DMA error");
		return;
	}

	if (unlikely(reason & B43_IRQ_UCODE_DEBUG))
		handle_irq_ucode_debug(dev);
	if (reason & B43_IRQ_TBTT_INDI)
		handle_irq_tbtt_indication(dev);
	if (reason & B43_IRQ_ATIM_END)
		handle_irq_atim_end(dev);
	if (reason & B43_IRQ_BEACON)
		handle_irq_beacon(dev);
	if (reason & B43_IRQ_PMQ)
		handle_irq_pmq(dev);
	if (reason & B43_IRQ_TXFIFO_FLUSH_OK)
		;/* TODO */
	if (reason & B43_IRQ_NOISESAMPLE_OK)
		handle_irq_noise(dev);

	/* Check the DMA reason registers for received data. */
	if (dma_reason[0] & B43_DMAIRQ_RDESC_UFLOW) {
		if (B43_DEBUG)
			b43warn(dev->wl, "RX descriptor underrun\n");
		b43_dma_handle_rx_overflow(dev->dma.rx_ring);
	}
	if (dma_reason[0] & B43_DMAIRQ_RX_DONE) {
		if (b43_using_pio_transfers(dev))
			b43_pio_rx(dev->pio.rx_queue);
		else
			b43_dma_rx(dev->dma.rx_ring);
	}
	B43_WARN_ON(dma_reason[1] & B43_DMAIRQ_RX_DONE);
	B43_WARN_ON(dma_reason[2] & B43_DMAIRQ_RX_DONE);
	B43_WARN_ON(dma_reason[3] & B43_DMAIRQ_RX_DONE);
	B43_WARN_ON(dma_reason[4] & B43_DMAIRQ_RX_DONE);
	B43_WARN_ON(dma_reason[5] & B43_DMAIRQ_RX_DONE);

	if (reason & B43_IRQ_TX_OK)
		handle_irq_transmit_status(dev);

	/* Re-enable interrupts on the device by restoring the current interrupt mask. */
	b43_write32(dev, B43_MMIO_GEN_IRQ_MASK, dev->irq_mask);

#if B43_DEBUG
	if (b43_debug(dev, B43_DBG_VERBOSESTATS)) {
		dev->irq_count++;
		for (i = 0; i < ARRAY_SIZE(dev->irq_bit_count); i++) {
			if (reason & (1 << i))
				dev->irq_bit_count[i]++;
		}
	}
#endif
}