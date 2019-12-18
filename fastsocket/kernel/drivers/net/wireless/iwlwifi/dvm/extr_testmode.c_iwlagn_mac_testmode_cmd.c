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
struct nlattr {int dummy; } ;
struct iwl_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  tst; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,...) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 size_t IWL_TM_ATTR_COMMAND ; 
 int IWL_TM_ATTR_MAX ; 
#define  IWL_TM_CMD_APP2DEV_BEGIN_TRACE 147 
#define  IWL_TM_CMD_APP2DEV_CFG_INIT_CALIB 146 
#define  IWL_TM_CMD_APP2DEV_DIRECT_REG_READ32 145 
#define  IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE32 144 
#define  IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE8 143 
#define  IWL_TM_CMD_APP2DEV_END_TRACE 142 
#define  IWL_TM_CMD_APP2DEV_FIXRATE_REQ 141 
#define  IWL_TM_CMD_APP2DEV_GET_DEVICENAME 140 
#define  IWL_TM_CMD_APP2DEV_GET_DEVICE_ID 139 
#define  IWL_TM_CMD_APP2DEV_GET_EEPROM 138 
#define  IWL_TM_CMD_APP2DEV_GET_FW_INFO 137 
#define  IWL_TM_CMD_APP2DEV_GET_FW_VERSION 136 
#define  IWL_TM_CMD_APP2DEV_INDIRECT_BUFFER_READ 135 
#define  IWL_TM_CMD_APP2DEV_INDIRECT_BUFFER_WRITE 134 
#define  IWL_TM_CMD_APP2DEV_LOAD_INIT_FW 133 
#define  IWL_TM_CMD_APP2DEV_LOAD_RUNTIME_FW 132 
#define  IWL_TM_CMD_APP2DEV_LOAD_WOWLAN_FW 131 
#define  IWL_TM_CMD_APP2DEV_NOTIFICATIONS 130 
#define  IWL_TM_CMD_APP2DEV_OWNERSHIP 129 
#define  IWL_TM_CMD_APP2DEV_UCODE 128 
 int iwl_test_handle_cmd (int /*<<< orphan*/ *,struct nlattr**) ; 
 int iwl_test_parse (int /*<<< orphan*/ *,struct nlattr**,void*,int) ; 
 int iwl_testmode_driver (struct ieee80211_hw*,struct nlattr**) ; 
 int iwl_testmode_ownership (struct ieee80211_hw*,struct nlattr**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nla_get_u32 (struct nlattr*) ; 

int iwlagn_mac_testmode_cmd(struct ieee80211_hw *hw, void *data, int len)
{
	struct nlattr *tb[IWL_TM_ATTR_MAX];
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	int result;

	result = iwl_test_parse(&priv->tst, tb, data, len);
	if (result)
		return result;

	/* in case multiple accesses to the device happens */
	mutex_lock(&priv->mutex);
	switch (nla_get_u32(tb[IWL_TM_ATTR_COMMAND])) {
	case IWL_TM_CMD_APP2DEV_UCODE:
	case IWL_TM_CMD_APP2DEV_DIRECT_REG_READ32:
	case IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE32:
	case IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE8:
	case IWL_TM_CMD_APP2DEV_BEGIN_TRACE:
	case IWL_TM_CMD_APP2DEV_END_TRACE:
	case IWL_TM_CMD_APP2DEV_INDIRECT_BUFFER_READ:
	case IWL_TM_CMD_APP2DEV_NOTIFICATIONS:
	case IWL_TM_CMD_APP2DEV_GET_FW_VERSION:
	case IWL_TM_CMD_APP2DEV_GET_DEVICE_ID:
	case IWL_TM_CMD_APP2DEV_INDIRECT_BUFFER_WRITE:
		result = iwl_test_handle_cmd(&priv->tst, tb);
		break;

	case IWL_TM_CMD_APP2DEV_GET_DEVICENAME:
	case IWL_TM_CMD_APP2DEV_LOAD_INIT_FW:
	case IWL_TM_CMD_APP2DEV_CFG_INIT_CALIB:
	case IWL_TM_CMD_APP2DEV_LOAD_RUNTIME_FW:
	case IWL_TM_CMD_APP2DEV_GET_EEPROM:
	case IWL_TM_CMD_APP2DEV_FIXRATE_REQ:
	case IWL_TM_CMD_APP2DEV_LOAD_WOWLAN_FW:
	case IWL_TM_CMD_APP2DEV_GET_FW_INFO:
		IWL_DEBUG_INFO(priv, "testmode cmd to driver\n");
		result = iwl_testmode_driver(hw, tb);
		break;

	case IWL_TM_CMD_APP2DEV_OWNERSHIP:
		IWL_DEBUG_INFO(priv, "testmode change uCode ownership\n");
		result = iwl_testmode_ownership(hw, tb);
		break;

	default:
		IWL_ERR(priv, "Unknown testmode command\n");
		result = -ENOSYS;
		break;
	}
	mutex_unlock(&priv->mutex);

	if (result)
		IWL_ERR(priv, "Test cmd failed result=%d\n", result);
	return result;
}