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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_PS_CTRL_MSK_PWR_SRC ; 
 int /*<<< orphan*/  APMG_PS_CTRL_REG ; 
 int /*<<< orphan*/  APMG_PS_CTRL_VAL_PWR_SRC_VMAIN ; 
 int /*<<< orphan*/  CSR_GPIO_IN ; 
 int /*<<< orphan*/  CSR_GPIO_IN_BIT_AUX_POWER ; 
 int /*<<< orphan*/  CSR_GPIO_IN_VAL_VMAIN_PWR_SRC ; 
 int /*<<< orphan*/  _il_poll_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  il_set_bits_mask_prph (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il3945_set_pwr_vmain(struct il_priv *il)
{
/*
 * (for documentation purposes)
 * to set power to V_AUX, do

		if (pci_pme_capable(il->pci_dev, PCI_D3cold)) {
			il_set_bits_mask_prph(il, APMG_PS_CTRL_REG,
					APMG_PS_CTRL_VAL_PWR_SRC_VAUX,
					~APMG_PS_CTRL_MSK_PWR_SRC);

			_il_poll_bit(il, CSR_GPIO_IN,
				     CSR_GPIO_IN_VAL_VAUX_PWR_SRC,
				     CSR_GPIO_IN_BIT_AUX_POWER, 5000);
		}
 */

	il_set_bits_mask_prph(il, APMG_PS_CTRL_REG,
			      APMG_PS_CTRL_VAL_PWR_SRC_VMAIN,
			      ~APMG_PS_CTRL_MSK_PWR_SRC);

	_il_poll_bit(il, CSR_GPIO_IN, CSR_GPIO_IN_VAL_VMAIN_PWR_SRC,
		     CSR_GPIO_IN_BIT_AUX_POWER, 5000);
}