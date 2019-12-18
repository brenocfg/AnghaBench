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
struct iwl_priv {int /*<<< orphan*/  trans; TYPE_2__* nvm_data; TYPE_1__* cfg; } ;
struct TYPE_4__ {int calib_version; } ;
struct TYPE_3__ {int device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_DRIVER_REG ; 
 int /*<<< orphan*/  CSR_GP_DRIVER_REG_BIT_6050_1x2 ; 
 int /*<<< orphan*/  CSR_GP_DRIVER_REG_BIT_CALIB_VERSION6 ; 
 int /*<<< orphan*/  CSR_GP_DRIVER_REG_BIT_RADIO_SKU_2x2_IPA ; 
#define  IWL_DEVICE_FAMILY_6000 133 
#define  IWL_DEVICE_FAMILY_6000i 132 
#define  IWL_DEVICE_FAMILY_6005 131 
#define  IWL_DEVICE_FAMILY_6030 130 
#define  IWL_DEVICE_FAMILY_6050 129 
#define  IWL_DEVICE_FAMILY_6150 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl6000_nic_config(struct iwl_priv *priv)
{
	switch (priv->cfg->device_family) {
	case IWL_DEVICE_FAMILY_6005:
	case IWL_DEVICE_FAMILY_6030:
	case IWL_DEVICE_FAMILY_6000:
		break;
	case IWL_DEVICE_FAMILY_6000i:
		/* 2x2 IPA phy type */
		iwl_write32(priv->trans, CSR_GP_DRIVER_REG,
			     CSR_GP_DRIVER_REG_BIT_RADIO_SKU_2x2_IPA);
		break;
	case IWL_DEVICE_FAMILY_6050:
		/* Indicate calibration version to uCode. */
		if (priv->nvm_data->calib_version >= 6)
			iwl_set_bit(priv->trans, CSR_GP_DRIVER_REG,
					CSR_GP_DRIVER_REG_BIT_CALIB_VERSION6);
		break;
	case IWL_DEVICE_FAMILY_6150:
		/* Indicate calibration version to uCode. */
		if (priv->nvm_data->calib_version >= 6)
			iwl_set_bit(priv->trans, CSR_GP_DRIVER_REG,
					CSR_GP_DRIVER_REG_BIT_CALIB_VERSION6);
		iwl_set_bit(priv->trans, CSR_GP_DRIVER_REG,
			    CSR_GP_DRIVER_REG_BIT_6050_1x2);
		break;
	default:
		WARN_ON(1);
	}
}