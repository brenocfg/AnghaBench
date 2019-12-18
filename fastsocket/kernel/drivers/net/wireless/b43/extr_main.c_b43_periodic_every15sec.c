#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ opensource; } ;
struct b43_phy {int /*<<< orphan*/  txerr_cnt; TYPE_2__* ops; } ;
struct b43_wldev {int irq_count; int tx_count; int rx_count; int* irq_bit_count; int /*<<< orphan*/  wl; TYPE_1__ fw; struct b43_phy phy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* pwork_15sec ) (struct b43_wldev*) ;} ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  B43_DBG_VERBOSESTATS ; 
 int /*<<< orphan*/  B43_PHY_TX_BADNESS_LIMIT ; 
 int /*<<< orphan*/  B43_SHM_SCRATCH ; 
 int /*<<< orphan*/  B43_WATCHDOG_REG ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_controller_restart (struct b43_wldev*,char*) ; 
 scalar_t__ b43_debug (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_shm_read16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,int,unsigned int,int) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct b43_wldev*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void b43_periodic_every15sec(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	u16 wdr;

	if (dev->fw.opensource) {
		/* Check if the firmware is still alive.
		 * It will reset the watchdog counter to 0 in its idle loop. */
		wdr = b43_shm_read16(dev, B43_SHM_SCRATCH, B43_WATCHDOG_REG);
		if (unlikely(wdr)) {
			b43err(dev->wl, "Firmware watchdog: The firmware died!\n");
			b43_controller_restart(dev, "Firmware watchdog");
			return;
		} else {
			b43_shm_write16(dev, B43_SHM_SCRATCH,
					B43_WATCHDOG_REG, 1);
		}
	}

	if (phy->ops->pwork_15sec)
		phy->ops->pwork_15sec(dev);

	atomic_set(&phy->txerr_cnt, B43_PHY_TX_BADNESS_LIMIT);
	wmb();

#if B43_DEBUG
	if (b43_debug(dev, B43_DBG_VERBOSESTATS)) {
		unsigned int i;

		b43dbg(dev->wl, "Stats: %7u IRQs/sec, %7u TX/sec, %7u RX/sec\n",
		       dev->irq_count / 15,
		       dev->tx_count / 15,
		       dev->rx_count / 15);
		dev->irq_count = 0;
		dev->tx_count = 0;
		dev->rx_count = 0;
		for (i = 0; i < ARRAY_SIZE(dev->irq_bit_count); i++) {
			if (dev->irq_bit_count[i]) {
				b43dbg(dev->wl, "Stats: %7u IRQ-%02u/sec (0x%08X)\n",
				       dev->irq_bit_count[i] / 15, i, (1 << i));
				dev->irq_bit_count[i] = 0;
			}
		}
	}
#endif
}