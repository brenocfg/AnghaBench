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
typedef  int u8 ;
struct il_priv {int /*<<< orphan*/  lock; TYPE_1__* pci_dev; scalar_t__ eeprom; } ;
struct il3945_eeprom {int sku_cap; int board_revision; int almgor_m_version; } ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR39_HW_IF_CONFIG_REG_BITS_SILICON_TYPE_A ; 
 int /*<<< orphan*/  CSR39_HW_IF_CONFIG_REG_BITS_SILICON_TYPE_B ; 
 int /*<<< orphan*/  CSR39_HW_IF_CONFIG_REG_BIT_3945_MB ; 
 int /*<<< orphan*/  CSR39_HW_IF_CONFIG_REG_BIT_3945_MM ; 
 int /*<<< orphan*/  CSR39_HW_IF_CONFIG_REG_BIT_BOARD_TYPE ; 
 int /*<<< orphan*/  CSR39_HW_IF_CONFIG_REG_BIT_SKU_MRC ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int /*<<< orphan*/  D_INFO (char*,...) ; 
 int /*<<< orphan*/  D_RF_KILL (char*) ; 
 int EEPROM_SKU_CAP_HW_RF_KILL_ENABLE ; 
 int EEPROM_SKU_CAP_OP_MODE_MRC ; 
 int EEPROM_SKU_CAP_SW_RF_KILL_ENABLE ; 
 int PCI_CFG_REV_ID_BIT_BASIC_SKU ; 
 int PCI_CFG_REV_ID_BIT_RTP ; 
 int /*<<< orphan*/  il_clear_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_set_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
il3945_nic_config(struct il_priv *il)
{
	struct il3945_eeprom *eeprom = (struct il3945_eeprom *)il->eeprom;
	unsigned long flags;
	u8 rev_id = il->pci_dev->revision;

	spin_lock_irqsave(&il->lock, flags);

	/* Determine HW type */
	D_INFO("HW Revision ID = 0x%X\n", rev_id);

	if (rev_id & PCI_CFG_REV_ID_BIT_RTP)
		D_INFO("RTP type\n");
	else if (rev_id & PCI_CFG_REV_ID_BIT_BASIC_SKU) {
		D_INFO("3945 RADIO-MB type\n");
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BIT_3945_MB);
	} else {
		D_INFO("3945 RADIO-MM type\n");
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BIT_3945_MM);
	}

	if (EEPROM_SKU_CAP_OP_MODE_MRC == eeprom->sku_cap) {
		D_INFO("SKU OP mode is mrc\n");
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BIT_SKU_MRC);
	} else
		D_INFO("SKU OP mode is basic\n");

	if ((eeprom->board_revision & 0xF0) == 0xD0) {
		D_INFO("3945ABG revision is 0x%X\n", eeprom->board_revision);
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BIT_BOARD_TYPE);
	} else {
		D_INFO("3945ABG revision is 0x%X\n", eeprom->board_revision);
		il_clear_bit(il, CSR_HW_IF_CONFIG_REG,
			     CSR39_HW_IF_CONFIG_REG_BIT_BOARD_TYPE);
	}

	if (eeprom->almgor_m_version <= 1) {
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BITS_SILICON_TYPE_A);
		D_INFO("Card M type A version is 0x%X\n",
		       eeprom->almgor_m_version);
	} else {
		D_INFO("Card M type B version is 0x%X\n",
		       eeprom->almgor_m_version);
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BITS_SILICON_TYPE_B);
	}
	spin_unlock_irqrestore(&il->lock, flags);

	if (eeprom->sku_cap & EEPROM_SKU_CAP_SW_RF_KILL_ENABLE)
		D_RF_KILL("SW RF KILL supported in EEPROM.\n");

	if (eeprom->sku_cap & EEPROM_SKU_CAP_HW_RF_KILL_ENABLE)
		D_RF_KILL("HW RF KILL supported in EEPROM.\n");
}