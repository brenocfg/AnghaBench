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
struct b43_wldev {int dfq_valid; int radio_hw_enable; int mac_suspended; int /*<<< orphan*/  noisecalc; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/ * dma_reason; scalar_t__ irq_reason; int /*<<< orphan*/  phy; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_IRQ_MASKTEMPLATE ; 
 int /*<<< orphan*/  B43_IRQ_PHY_TXERR ; 
 scalar_t__ B43_VERBOSITY_DEBUG ; 
 scalar_t__ b43_modparam_verbose ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_struct_phy_for_init (struct b43_wldev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_struct_wldev_for_init(struct b43_wldev *dev)
{
	dev->dfq_valid = false;

	/* Assume the radio is enabled. If it's not enabled, the state will
	 * immediately get fixed on the first periodic work run. */
	dev->radio_hw_enable = true;

	/* Stats */
	memset(&dev->stats, 0, sizeof(dev->stats));

	setup_struct_phy_for_init(dev, &dev->phy);

	/* IRQ related flags */
	dev->irq_reason = 0;
	memset(dev->dma_reason, 0, sizeof(dev->dma_reason));
	dev->irq_mask = B43_IRQ_MASKTEMPLATE;
	if (b43_modparam_verbose < B43_VERBOSITY_DEBUG)
		dev->irq_mask &= ~B43_IRQ_PHY_TXERR;

	dev->mac_suspended = 1;

	/* Noise calculation context */
	memset(&dev->noisecalc, 0, sizeof(dev->noisecalc));
}