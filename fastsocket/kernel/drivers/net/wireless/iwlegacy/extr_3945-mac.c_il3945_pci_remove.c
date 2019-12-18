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
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {int /*<<< orphan*/  irq; TYPE_1__ dev; } ;
struct TYPE_6__ {scalar_t__ bd; } ;
struct TYPE_5__ {int /*<<< orphan*/  rfkill_poll; } ;
struct il_priv {int /*<<< orphan*/  hw; scalar_t__ beacon_skb; int /*<<< orphan*/  scan_cmd; int /*<<< orphan*/  hw_base; int /*<<< orphan*/ * workqueue; TYPE_3__ rxq; TYPE_2__ _3945; int /*<<< orphan*/  lock; scalar_t__ mac80211_registered; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct il_priv*) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il3945_attribute_group ; 
 int /*<<< orphan*/  il3945_dealloc_ucode_pci (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_down (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_hw_txq_ctx_free (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_rx_queue_free (struct il_priv*,TYPE_3__*) ; 
 int /*<<< orphan*/  il3945_synchronize_irq (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_unset_hw_params (struct il_priv*) ; 
 int /*<<< orphan*/  il_apm_stop (struct il_priv*) ; 
 int /*<<< orphan*/  il_dbgfs_unregister (struct il_priv*) ; 
 int /*<<< orphan*/  il_disable_interrupts (struct il_priv*) ; 
 int /*<<< orphan*/  il_free_channel_map (struct il_priv*) ; 
 int /*<<< orphan*/  il_free_geos (struct il_priv*) ; 
 int /*<<< orphan*/  il_leds_exit (struct il_priv*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct il_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il3945_pci_remove(struct pci_dev *pdev)
{
	struct il_priv *il = pci_get_drvdata(pdev);
	unsigned long flags;

	if (!il)
		return;

	D_INFO("*** UNLOAD DRIVER ***\n");

	il_dbgfs_unregister(il);

	set_bit(S_EXIT_PENDING, &il->status);

	il_leds_exit(il);

	if (il->mac80211_registered) {
		ieee80211_unregister_hw(il->hw);
		il->mac80211_registered = 0;
	} else {
		il3945_down(il);
	}

	/*
	 * Make sure device is reset to low power before unloading driver.
	 * This may be redundant with il_down(), but there are paths to
	 * run il_down() without calling apm_ops.stop(), and there are
	 * paths to avoid running il_down() at all before leaving driver.
	 * This (inexpensive) call *makes sure* device is reset.
	 */
	il_apm_stop(il);

	/* make sure we flush any pending irq or
	 * tasklet for the driver
	 */
	spin_lock_irqsave(&il->lock, flags);
	il_disable_interrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);

	il3945_synchronize_irq(il);

	sysfs_remove_group(&pdev->dev.kobj, &il3945_attribute_group);

	cancel_delayed_work_sync(&il->_3945.rfkill_poll);

	il3945_dealloc_ucode_pci(il);

	if (il->rxq.bd)
		il3945_rx_queue_free(il, &il->rxq);
	il3945_hw_txq_ctx_free(il);

	il3945_unset_hw_params(il);

	/*netif_stop_queue(dev); */
	flush_workqueue(il->workqueue);

	/* ieee80211_unregister_hw calls il3945_mac_stop, which flushes
	 * il->workqueue... so we can't take down the workqueue
	 * until now... */
	destroy_workqueue(il->workqueue);
	il->workqueue = NULL;

	free_irq(pdev->irq, il);
	pci_disable_msi(pdev);

	iounmap(il->hw_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);

	il_free_channel_map(il);
	il_free_geos(il);
	kfree(il->scan_cmd);
	if (il->beacon_skb)
		dev_kfree_skb(il->beacon_skb);

	ieee80211_free_hw(il->hw);
}