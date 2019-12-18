#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  rx_ring3; int /*<<< orphan*/  rx_ring0; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue3; int /*<<< orphan*/  queue0; } ;
struct TYPE_5__ {int /*<<< orphan*/  txerr_cnt; } ;
struct b43legacy_wldev {int* dma_reason; int irq_reason; TYPE_4__* wl; int /*<<< orphan*/  irq_mask; TYPE_3__ dma; TYPE_2__ pio; TYPE_1__ phy; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int B43legacy_DMAIRQ_FATALMASK ; 
 int B43legacy_DMAIRQ_NONFATALMASK ; 
 int B43legacy_DMAIRQ_RX_DONE ; 
 int B43legacy_IRQ_ATIM_END ; 
 int B43legacy_IRQ_BEACON ; 
 int B43legacy_IRQ_MAC_TXERR ; 
 int B43legacy_IRQ_NOISESAMPLE_OK ; 
 int B43legacy_IRQ_PHY_TXERR ; 
 int B43legacy_IRQ_PMQ ; 
 int B43legacy_IRQ_TBTT_INDI ; 
 int B43legacy_IRQ_TXFIFO_FLUSH_OK ; 
 int B43legacy_IRQ_TX_OK ; 
 int B43legacy_IRQ_UCODE_DEBUG ; 
 int /*<<< orphan*/  B43legacy_MMIO_GEN_IRQ_MASK ; 
 scalar_t__ B43legacy_STAT_INITIALIZED ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b43legacy_controller_restart (struct b43legacy_wldev*,char*) ; 
 int /*<<< orphan*/  b43legacy_dma_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_pio_rx (int /*<<< orphan*/ ) ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 scalar_t__ b43legacy_using_pio (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacyerr (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  handle_irq_atim_end (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  handle_irq_beacon (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  handle_irq_noise (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  handle_irq_pmq (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  handle_irq_tbtt_indication (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  handle_irq_transmit_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  handle_irq_ucode_debug (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void b43legacy_interrupt_tasklet(struct b43legacy_wldev *dev)
{
	u32 reason;
	u32 dma_reason[ARRAY_SIZE(dev->dma_reason)];
	u32 merged_dma_reason = 0;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&dev->wl->irq_lock, flags);

	B43legacy_WARN_ON(b43legacy_status(dev) <
			  B43legacy_STAT_INITIALIZED);

	reason = dev->irq_reason;
	for (i = 0; i < ARRAY_SIZE(dma_reason); i++) {
		dma_reason[i] = dev->dma_reason[i];
		merged_dma_reason |= dma_reason[i];
	}

	if (unlikely(reason & B43legacy_IRQ_MAC_TXERR))
		b43legacyerr(dev->wl, "MAC transmission error\n");

	if (unlikely(reason & B43legacy_IRQ_PHY_TXERR)) {
		b43legacyerr(dev->wl, "PHY transmission error\n");
		rmb();
		if (unlikely(atomic_dec_and_test(&dev->phy.txerr_cnt))) {
			b43legacyerr(dev->wl, "Too many PHY TX errors, "
					      "restarting the controller\n");
			b43legacy_controller_restart(dev, "PHY TX errors");
		}
	}

	if (unlikely(merged_dma_reason & (B43legacy_DMAIRQ_FATALMASK |
					  B43legacy_DMAIRQ_NONFATALMASK))) {
		if (merged_dma_reason & B43legacy_DMAIRQ_FATALMASK) {
			b43legacyerr(dev->wl, "Fatal DMA error: "
			       "0x%08X, 0x%08X, 0x%08X, "
			       "0x%08X, 0x%08X, 0x%08X\n",
			       dma_reason[0], dma_reason[1],
			       dma_reason[2], dma_reason[3],
			       dma_reason[4], dma_reason[5]);
			b43legacy_controller_restart(dev, "DMA error");
			mmiowb();
			spin_unlock_irqrestore(&dev->wl->irq_lock, flags);
			return;
		}
		if (merged_dma_reason & B43legacy_DMAIRQ_NONFATALMASK)
			b43legacyerr(dev->wl, "DMA error: "
			       "0x%08X, 0x%08X, 0x%08X, "
			       "0x%08X, 0x%08X, 0x%08X\n",
			       dma_reason[0], dma_reason[1],
			       dma_reason[2], dma_reason[3],
			       dma_reason[4], dma_reason[5]);
	}

	if (unlikely(reason & B43legacy_IRQ_UCODE_DEBUG))
		handle_irq_ucode_debug(dev);
	if (reason & B43legacy_IRQ_TBTT_INDI)
		handle_irq_tbtt_indication(dev);
	if (reason & B43legacy_IRQ_ATIM_END)
		handle_irq_atim_end(dev);
	if (reason & B43legacy_IRQ_BEACON)
		handle_irq_beacon(dev);
	if (reason & B43legacy_IRQ_PMQ)
		handle_irq_pmq(dev);
	if (reason & B43legacy_IRQ_TXFIFO_FLUSH_OK)
		;/*TODO*/
	if (reason & B43legacy_IRQ_NOISESAMPLE_OK)
		handle_irq_noise(dev);

	/* Check the DMA reason registers for received data. */
	if (dma_reason[0] & B43legacy_DMAIRQ_RX_DONE) {
		if (b43legacy_using_pio(dev))
			b43legacy_pio_rx(dev->pio.queue0);
		else
			b43legacy_dma_rx(dev->dma.rx_ring0);
	}
	B43legacy_WARN_ON(dma_reason[1] & B43legacy_DMAIRQ_RX_DONE);
	B43legacy_WARN_ON(dma_reason[2] & B43legacy_DMAIRQ_RX_DONE);
	if (dma_reason[3] & B43legacy_DMAIRQ_RX_DONE) {
		if (b43legacy_using_pio(dev))
			b43legacy_pio_rx(dev->pio.queue3);
		else
			b43legacy_dma_rx(dev->dma.rx_ring3);
	}
	B43legacy_WARN_ON(dma_reason[4] & B43legacy_DMAIRQ_RX_DONE);
	B43legacy_WARN_ON(dma_reason[5] & B43legacy_DMAIRQ_RX_DONE);

	if (reason & B43legacy_IRQ_TX_OK)
		handle_irq_transmit_status(dev);

	b43legacy_write32(dev, B43legacy_MMIO_GEN_IRQ_MASK, dev->irq_mask);
	mmiowb();
	spin_unlock_irqrestore(&dev->wl->irq_lock, flags);
}