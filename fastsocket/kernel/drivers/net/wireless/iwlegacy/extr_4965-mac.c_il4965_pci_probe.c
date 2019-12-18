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
typedef  int u16 ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  firmware_loading_complete; } ;
struct il_priv {unsigned long long hw_base; struct ieee80211_hw* hw; struct pci_dev* pci_dev; int /*<<< orphan*/ * workqueue; TYPE_2__ _4965; int /*<<< orphan*/  status; int /*<<< orphan*/  lock; TYPE_1__* addresses; int /*<<< orphan*/  hw_ready; int /*<<< orphan*/  hw_rev; struct il_cfg* cfg; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  inta_mask; int /*<<< orphan*/ * debugfs_ops; int /*<<< orphan*/ * ops; } ;
struct il_cfg {int /*<<< orphan*/  name; } ;
struct ieee80211_hw {TYPE_3__* wiphy; struct il_priv* priv; } ;
struct TYPE_6__ {int n_addresses; TYPE_1__* addresses; } ;
struct TYPE_4__ {unsigned long long addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW ; 
 int /*<<< orphan*/  CSR_INI_SET_MASK ; 
 int /*<<< orphan*/  CSR_RESET ; 
 int /*<<< orphan*/  CSR_RESET_REG_FLAG_NEVO_RESET ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  D_INFO (char*,...) ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IL_ERR (char*,...) ; 
 int /*<<< orphan*/  IL_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IL_WARN (char*) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int PCIE_LINK_STATE_CLKPM ; 
 int PCIE_LINK_STATE_L0S ; 
 int PCIE_LINK_STATE_L1 ; 
 int /*<<< orphan*/  PCI_CFG_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_INTX_DISABLE ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_RFKILL ; 
 int _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct il_priv*) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  il4965_debugfs_ops ; 
 int il4965_eeprom_check_version (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_eeprom_get_mac (struct il_priv*,unsigned long long) ; 
 int /*<<< orphan*/  il4965_hw_detect (struct il_priv*) ; 
 int il4965_init_drv (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_mac_ops ; 
 int /*<<< orphan*/  il4965_ops ; 
 int /*<<< orphan*/  il4965_prepare_card_hw (struct il_priv*) ; 
 int il4965_request_firmware (struct il_priv*,int) ; 
 int /*<<< orphan*/  il4965_set_hw_params (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_setup_deferred_work (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_setup_handlers (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_uninit_drv (struct il_priv*) ; 
 int /*<<< orphan*/  il_disable_interrupts (struct il_priv*) ; 
 int /*<<< orphan*/  il_eeprom_free (struct il_priv*) ; 
 int il_eeprom_init (struct il_priv*) ; 
 int /*<<< orphan*/  il_enable_rfkill_int (struct il_priv*) ; 
 int /*<<< orphan*/  il_isr ; 
 int /*<<< orphan*/  il_power_initialize (struct il_priv*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (unsigned long long) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_link_state (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 unsigned long long pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct il_priv*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct il_priv*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
il4965_pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int err = 0;
	struct il_priv *il;
	struct ieee80211_hw *hw;
	struct il_cfg *cfg = (struct il_cfg *)(ent->driver_data);
	unsigned long flags;
	u16 pci_cmd;

	/************************
	 * 1. Allocating HW data
	 ************************/

	hw = ieee80211_alloc_hw(sizeof(struct il_priv), &il4965_mac_ops);
	if (!hw) {
		err = -ENOMEM;
		goto out;
	}
	il = hw->priv;
	il->hw = hw;
	SET_IEEE80211_DEV(hw, &pdev->dev);

	D_INFO("*** LOAD DRIVER ***\n");
	il->cfg = cfg;
	il->ops = &il4965_ops;
#ifdef CONFIG_IWLEGACY_DEBUGFS
	il->debugfs_ops = &il4965_debugfs_ops;
#endif
	il->pci_dev = pdev;
	il->inta_mask = CSR_INI_SET_MASK;

	/**************************
	 * 2. Initializing PCI bus
	 **************************/
	pci_disable_link_state(pdev,
			       PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 |
			       PCIE_LINK_STATE_CLKPM);

	if (pci_enable_device(pdev)) {
		err = -ENODEV;
		goto out_ieee80211_free_hw;
	}

	pci_set_master(pdev);

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(36));
	if (!err)
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(36));
	if (err) {
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (!err)
			err =
			    pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		/* both attempts failed: */
		if (err) {
			IL_WARN("No suitable DMA available.\n");
			goto out_pci_disable_device;
		}
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err)
		goto out_pci_disable_device;

	pci_set_drvdata(pdev, il);

	/***********************
	 * 3. Read REV register
	 ***********************/
	il->hw_base = pci_ioremap_bar(pdev, 0);
	if (!il->hw_base) {
		err = -ENODEV;
		goto out_pci_release_regions;
	}

	D_INFO("pci_resource_len = 0x%08llx\n",
	       (unsigned long long)pci_resource_len(pdev, 0));
	D_INFO("pci_resource_base = %p\n", il->hw_base);

	/* these spin locks will be used in apm_ops.init and EEPROM access
	 * we should init now
	 */
	spin_lock_init(&il->reg_lock);
	spin_lock_init(&il->lock);

	/*
	 * stop and reset the on-board processor just in case it is in a
	 * strange state ... like being left stranded by a primary kernel
	 * and this is now the kdump kernel trying to start up
	 */
	_il_wr(il, CSR_RESET, CSR_RESET_REG_FLAG_NEVO_RESET);

	il4965_hw_detect(il);
	IL_INFO("Detected %s, REV=0x%X\n", il->cfg->name, il->hw_rev);

	/* We disable the RETRY_TIMEOUT register (0x41) to keep
	 * PCI Tx retries from interfering with C3 CPU state */
	pci_write_config_byte(pdev, PCI_CFG_RETRY_TIMEOUT, 0x00);

	il4965_prepare_card_hw(il);
	if (!il->hw_ready) {
		IL_WARN("Failed, HW not ready\n");
		err = -EIO;
		goto out_iounmap;
	}

	/*****************
	 * 4. Read EEPROM
	 *****************/
	/* Read the EEPROM */
	err = il_eeprom_init(il);
	if (err) {
		IL_ERR("Unable to init EEPROM\n");
		goto out_iounmap;
	}
	err = il4965_eeprom_check_version(il);
	if (err)
		goto out_free_eeprom;

	/* extract MAC Address */
	il4965_eeprom_get_mac(il, il->addresses[0].addr);
	D_INFO("MAC address: %pM\n", il->addresses[0].addr);
	il->hw->wiphy->addresses = il->addresses;
	il->hw->wiphy->n_addresses = 1;

	/************************
	 * 5. Setup HW constants
	 ************************/
	il4965_set_hw_params(il);

	/*******************
	 * 6. Setup il
	 *******************/

	err = il4965_init_drv(il);
	if (err)
		goto out_free_eeprom;
	/* At this point both hw and il are initialized. */

	/********************
	 * 7. Setup services
	 ********************/
	spin_lock_irqsave(&il->lock, flags);
	il_disable_interrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);

	pci_enable_msi(il->pci_dev);

	err = request_irq(il->pci_dev->irq, il_isr, IRQF_SHARED, DRV_NAME, il);
	if (err) {
		IL_ERR("Error allocating IRQ %d\n", il->pci_dev->irq);
		goto out_disable_msi;
	}

	il4965_setup_deferred_work(il);
	il4965_setup_handlers(il);

	/*********************************************
	 * 8. Enable interrupts and read RFKILL state
	 *********************************************/

	/* enable rfkill interrupt: hw bug w/a */
	pci_read_config_word(il->pci_dev, PCI_COMMAND, &pci_cmd);
	if (pci_cmd & PCI_COMMAND_INTX_DISABLE) {
		pci_cmd &= ~PCI_COMMAND_INTX_DISABLE;
		pci_write_config_word(il->pci_dev, PCI_COMMAND, pci_cmd);
	}

	il_enable_rfkill_int(il);

	/* If platform's RF_KILL switch is NOT set to KILL */
	if (_il_rd(il, CSR_GP_CNTRL) & CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW)
		clear_bit(S_RFKILL, &il->status);
	else
		set_bit(S_RFKILL, &il->status);

	wiphy_rfkill_set_hw_state(il->hw->wiphy,
				  test_bit(S_RFKILL, &il->status));

	il_power_initialize(il);

	init_completion(&il->_4965.firmware_loading_complete);

	err = il4965_request_firmware(il, true);
	if (err)
		goto out_destroy_workqueue;

	return 0;

out_destroy_workqueue:
	destroy_workqueue(il->workqueue);
	il->workqueue = NULL;
	free_irq(il->pci_dev->irq, il);
out_disable_msi:
	pci_disable_msi(il->pci_dev);
	il4965_uninit_drv(il);
out_free_eeprom:
	il_eeprom_free(il);
out_iounmap:
	iounmap(il->hw_base);
out_pci_release_regions:
	pci_set_drvdata(pdev, NULL);
	pci_release_regions(pdev);
out_pci_disable_device:
	pci_disable_device(pdev);
out_ieee80211_free_hw:
	ieee80211_free_hw(il->hw);
out:
	return err;
}