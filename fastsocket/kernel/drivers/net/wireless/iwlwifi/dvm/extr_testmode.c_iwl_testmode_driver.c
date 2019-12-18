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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct iwl_trans {int dummy; } ;
struct iwl_priv {int ucode_loaded; unsigned char* eeprom_blob; int eeprom_blob_size; int tm_fixed_rate; size_t cur_ucode; TYPE_2__* fw; TYPE_1__* cfg; struct iwl_trans* trans; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct fw_img {TYPE_3__* sec; } ;
struct TYPE_6__ {size_t len; } ;
struct TYPE_5__ {struct fw_img* img; } ;
struct TYPE_4__ {scalar_t__ name; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENODATA ; 
 int ENOMEM ; 
 int ENOMSG ; 
 int ENOSYS ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,...) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 size_t IWL_TM_ATTR_COMMAND ; 
 int /*<<< orphan*/  IWL_TM_ATTR_EEPROM ; 
 size_t IWL_TM_ATTR_FIXRATE ; 
 size_t IWL_TM_ATTR_FW_DATA_SIZE ; 
 size_t IWL_TM_ATTR_FW_INST_SIZE ; 
 size_t IWL_TM_ATTR_FW_TYPE ; 
 int /*<<< orphan*/  IWL_TM_ATTR_SYNC_RSP ; 
#define  IWL_TM_CMD_APP2DEV_CFG_INIT_CALIB 135 
#define  IWL_TM_CMD_APP2DEV_FIXRATE_REQ 134 
#define  IWL_TM_CMD_APP2DEV_GET_DEVICENAME 133 
#define  IWL_TM_CMD_APP2DEV_GET_EEPROM 132 
#define  IWL_TM_CMD_APP2DEV_GET_FW_INFO 131 
#define  IWL_TM_CMD_APP2DEV_LOAD_INIT_FW 130 
#define  IWL_TM_CMD_APP2DEV_LOAD_RUNTIME_FW 129 
#define  IWL_TM_CMD_APP2DEV_LOAD_WOWLAN_FW 128 
 size_t IWL_TM_CMD_DEV2APP_EEPROM_RSP ; 
 size_t IWL_TM_CMD_DEV2APP_SYNC_RSP ; 
 int /*<<< orphan*/  IWL_UCODE_INIT ; 
 int /*<<< orphan*/  IWL_UCODE_REGULAR ; 
 size_t IWL_UCODE_SECTION_DATA ; 
 size_t IWL_UCODE_SECTION_INST ; 
 int /*<<< orphan*/  IWL_UCODE_WOWLAN ; 
 struct sk_buff* cfg80211_testmode_alloc_reply_skb (int /*<<< orphan*/ ,int) ; 
 int cfg80211_testmode_reply (struct sk_buff*) ; 
 int iwl_alive_start (struct iwl_priv*) ; 
 int iwl_load_ucode_wait_alive (struct iwl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_scan_cancel_timeout (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  iwl_testmode_cfg_init_calib (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_trans_stop_device (struct iwl_trans*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  nla_put_u32 (struct sk_buff*,size_t,size_t) ; 
 int strlen (scalar_t__) ; 

__attribute__((used)) static int iwl_testmode_driver(struct ieee80211_hw *hw, struct nlattr **tb)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	struct iwl_trans *trans = priv->trans;
	struct sk_buff *skb;
	unsigned char *rsp_data_ptr = NULL;
	int status = 0, rsp_data_len = 0;
	u32 inst_size = 0, data_size = 0;
	const struct fw_img *img;

	switch (nla_get_u32(tb[IWL_TM_ATTR_COMMAND])) {
	case IWL_TM_CMD_APP2DEV_GET_DEVICENAME:
		rsp_data_ptr = (unsigned char *)priv->cfg->name;
		rsp_data_len = strlen(priv->cfg->name);
		skb = cfg80211_testmode_alloc_reply_skb(hw->wiphy,
							rsp_data_len + 20);
		if (!skb) {
			IWL_ERR(priv, "Memory allocation fail\n");
			return -ENOMEM;
		}
		if (nla_put_u32(skb, IWL_TM_ATTR_COMMAND,
				IWL_TM_CMD_DEV2APP_SYNC_RSP) ||
		    nla_put(skb, IWL_TM_ATTR_SYNC_RSP,
			    rsp_data_len, rsp_data_ptr))
			goto nla_put_failure;
		status = cfg80211_testmode_reply(skb);
		if (status < 0)
			IWL_ERR(priv, "Error sending msg : %d\n", status);
		break;

	case IWL_TM_CMD_APP2DEV_LOAD_INIT_FW:
		status = iwl_load_ucode_wait_alive(priv, IWL_UCODE_INIT);
		if (status)
			IWL_ERR(priv, "Error loading init ucode: %d\n", status);
		break;

	case IWL_TM_CMD_APP2DEV_CFG_INIT_CALIB:
		iwl_testmode_cfg_init_calib(priv);
		priv->ucode_loaded = false;
		iwl_trans_stop_device(trans);
		break;

	case IWL_TM_CMD_APP2DEV_LOAD_RUNTIME_FW:
		status = iwl_load_ucode_wait_alive(priv, IWL_UCODE_REGULAR);
		if (status) {
			IWL_ERR(priv,
				"Error loading runtime ucode: %d\n", status);
			break;
		}
		status = iwl_alive_start(priv);
		if (status)
			IWL_ERR(priv,
				"Error starting the device: %d\n", status);
		break;

	case IWL_TM_CMD_APP2DEV_LOAD_WOWLAN_FW:
		iwl_scan_cancel_timeout(priv, 200);
		priv->ucode_loaded = false;
		iwl_trans_stop_device(trans);
		status = iwl_load_ucode_wait_alive(priv, IWL_UCODE_WOWLAN);
		if (status) {
			IWL_ERR(priv,
				"Error loading WOWLAN ucode: %d\n", status);
			break;
		}
		status = iwl_alive_start(priv);
		if (status)
			IWL_ERR(priv,
				"Error starting the device: %d\n", status);
		break;

	case IWL_TM_CMD_APP2DEV_GET_EEPROM:
		if (priv->eeprom_blob) {
			skb = cfg80211_testmode_alloc_reply_skb(hw->wiphy,
				priv->eeprom_blob_size + 20);
			if (!skb) {
				IWL_ERR(priv, "Memory allocation fail\n");
				return -ENOMEM;
			}
			if (nla_put_u32(skb, IWL_TM_ATTR_COMMAND,
					IWL_TM_CMD_DEV2APP_EEPROM_RSP) ||
			    nla_put(skb, IWL_TM_ATTR_EEPROM,
				    priv->eeprom_blob_size,
				    priv->eeprom_blob))
				goto nla_put_failure;
			status = cfg80211_testmode_reply(skb);
			if (status < 0)
				IWL_ERR(priv, "Error sending msg : %d\n",
					status);
		} else
			return -ENODATA;
		break;

	case IWL_TM_CMD_APP2DEV_FIXRATE_REQ:
		if (!tb[IWL_TM_ATTR_FIXRATE]) {
			IWL_ERR(priv, "Missing fixrate setting\n");
			return -ENOMSG;
		}
		priv->tm_fixed_rate = nla_get_u32(tb[IWL_TM_ATTR_FIXRATE]);
		break;

	case IWL_TM_CMD_APP2DEV_GET_FW_INFO:
		skb = cfg80211_testmode_alloc_reply_skb(hw->wiphy, 20 + 8);
		if (!skb) {
			IWL_ERR(priv, "Memory allocation fail\n");
			return -ENOMEM;
		}
		if (!priv->ucode_loaded) {
			IWL_ERR(priv, "No uCode has not been loaded\n");
			return -EINVAL;
		} else {
			img = &priv->fw->img[priv->cur_ucode];
			inst_size = img->sec[IWL_UCODE_SECTION_INST].len;
			data_size = img->sec[IWL_UCODE_SECTION_DATA].len;
		}
		if (nla_put_u32(skb, IWL_TM_ATTR_FW_TYPE, priv->cur_ucode) ||
		    nla_put_u32(skb, IWL_TM_ATTR_FW_INST_SIZE, inst_size) ||
		    nla_put_u32(skb, IWL_TM_ATTR_FW_DATA_SIZE, data_size))
			goto nla_put_failure;
		status = cfg80211_testmode_reply(skb);
		if (status < 0)
			IWL_ERR(priv, "Error sending msg : %d\n", status);
		break;

	default:
		IWL_ERR(priv, "Unknown testmode driver command ID\n");
		return -ENOSYS;
	}
	return status;

nla_put_failure:
	kfree_skb(skb);
	return -EMSGSIZE;
}