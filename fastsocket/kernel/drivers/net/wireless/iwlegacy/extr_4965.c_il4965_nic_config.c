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
typedef  int /*<<< orphan*/  u16 ;
struct il_priv {int /*<<< orphan*/  lock; struct il_eeprom_calib_info* calib_info; } ;
struct il_eeprom_calib_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int CSR_HW_IF_CONFIG_REG_BIT_MAC_SI ; 
 int CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI ; 
 int /*<<< orphan*/  EEPROM_4965_CALIB_TXPOWER_OFFSET ; 
 int EEPROM_4965_RF_CFG_TYPE_MAX ; 
 int /*<<< orphan*/  EEPROM_RADIO_CONFIG ; 
 int EEPROM_RF_CFG_DASH_MSK (int /*<<< orphan*/ ) ; 
 int EEPROM_RF_CFG_STEP_MSK (int /*<<< orphan*/ ) ; 
 int EEPROM_RF_CFG_TYPE_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_eeprom_query16 (struct il_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ il_eeprom_query_addr (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_set_bit (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
il4965_nic_config(struct il_priv *il)
{
	unsigned long flags;
	u16 radio_cfg;

	spin_lock_irqsave(&il->lock, flags);

	radio_cfg = il_eeprom_query16(il, EEPROM_RADIO_CONFIG);

	/* write radio config values to register */
	if (EEPROM_RF_CFG_TYPE_MSK(radio_cfg) == EEPROM_4965_RF_CFG_TYPE_MAX)
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   EEPROM_RF_CFG_TYPE_MSK(radio_cfg) |
			   EEPROM_RF_CFG_STEP_MSK(radio_cfg) |
			   EEPROM_RF_CFG_DASH_MSK(radio_cfg));

	/* set CSR_HW_CONFIG_REG for uCode use */
	il_set_bit(il, CSR_HW_IF_CONFIG_REG,
		   CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI |
		   CSR_HW_IF_CONFIG_REG_BIT_MAC_SI);

	il->calib_info =
	    (struct il_eeprom_calib_info *)
	    il_eeprom_query_addr(il, EEPROM_4965_CALIB_TXPOWER_OFFSET);

	spin_unlock_irqrestore(&il->lock, flags);
}