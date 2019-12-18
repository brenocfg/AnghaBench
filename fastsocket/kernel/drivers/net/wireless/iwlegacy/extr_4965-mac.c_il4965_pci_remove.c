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
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {TYPE_2__ dev; } ;
struct TYPE_8__ {scalar_t__ bd; } ;
struct TYPE_5__ {int /*<<< orphan*/  firmware_loading_complete; } ;
struct il_priv {int /*<<< orphan*/  hw; int /*<<< orphan*/  beacon_skb; int /*<<< orphan*/  hw_base; TYPE_3__* pci_dev; int /*<<< orphan*/ * workqueue; TYPE_4__ rxq; int /*<<< orphan*/  lock; scalar_t__ mac80211_registered; int /*<<< orphan*/  status; TYPE_1__ _4965; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct il_priv*) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_dealloc_ucode_pci (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_down (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_hw_txq_ctx_free (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_rx_queue_free (struct il_priv*,TYPE_4__*) ; 
 int /*<<< orphan*/  il4965_synchronize_irq (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_uninit_drv (struct il_priv*) ; 
 int /*<<< orphan*/  il_apm_stop (struct il_priv*) ; 
 int /*<<< orphan*/  il_attribute_group ; 
 int /*<<< orphan*/  il_dbgfs_unregister (struct il_priv*) ; 
 int /*<<< orphan*/  il_disable_interrupts (struct il_priv*) ; 
 int /*<<< orphan*/  il_eeprom_free (struct il_priv*) ; 
 int /*<<< orphan*/  il_leds_exit (struct il_priv*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_3__*) ; 
 struct il_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il4965_pci_remove(struct pci_dev *pdev)
{
	struct il_priv *il = pci_get_drvdata(pdev);
	unsigned long flags;

	if (!il)
		return;

	wait_for_completion(&il->_4965.firmware_loading_complete);

	D_INFO("*** UNLOAD DRIVER ***\n");

	il_dbgfs_unregister(il);
	sysfs_remove_group(&pdev->dev.kobj, &il_attribute_group);

	/* ieee80211_unregister_hw call wil cause il_mac_stop to
	 * to be called and il4965_down since we are removing the device
	 * we need to set S_EXIT_PENDING bit.
	 */
	set_bit(S_EXIT_PENDING, &il->status);

	il_leds_exit(il);

	if (il->mac80211_registered) {
		ieee80211_unregister_hw(il->hw);
		il->mac80211_registered = 0;
	} else {
		il4965_down(il);
	}

	/*
	 * Make sure device is reset to low power before unloading driver.
	 * This may be redundant with il4965_down(), but there are paths to
	 * run il4965_down() without calling apm_ops.stop(), and there are
	 * paths to avoid running il4965_down() at all before leaving driver.
	 * This (inexpensive) call *makes sure* device is reset.
	 */
	il_apm_stop(il);

	/* make sure we flush any pending irq or
	 * tasklet for the driver
	 */
	spin_lock_irqsave(&il->lock, flags);
	il_disable_interrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);

	il4965_synchronize_irq(il);

	il4965_dealloc_ucode_pci(il);

	if (il->rxq.bd)
		il4965_rx_queue_free(il, &il->rxq);
	il4965_hw_txq_ctx_free(il);

	il_eeprom_free(il);

	/*netif_stop_queue(dev); */
	flush_workqueue(il->workqueue);

	/* ieee80211_unregister_hw calls il_mac_stop, which flushes
	 * il->workqueue... so we can't take down the workqueue
	 * until now... */
	destroy_workqueue(il->workqueue);
	il->workqueue = NULL;

	free_irq(il->pci_dev->irq, il);
	pci_disable_msi(il->pci_dev);
	iounmap(il->hw_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);

	il4965_uninit_drv(il);

	dev_kfree_skb(il->beacon_skb);

	ieee80211_free_hw(il->hw);
}