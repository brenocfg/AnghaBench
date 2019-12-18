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
typedef  scalar_t__ u8 ;
struct nlattr {int dummy; } ;
struct iwl_priv {int /*<<< orphan*/  tst; scalar_t__ ucode_owner; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMSG ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 scalar_t__ IWL_OWNERSHIP_DRIVER ; 
 scalar_t__ IWL_OWNERSHIP_TM ; 
 size_t IWL_TM_ATTR_UCODE_OWNER ; 
 int /*<<< orphan*/  iwl_test_enable_notifications (int /*<<< orphan*/ *,int) ; 
 scalar_t__ nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static int iwl_testmode_ownership(struct ieee80211_hw *hw, struct nlattr **tb)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	u8 owner;

	if (!tb[IWL_TM_ATTR_UCODE_OWNER]) {
		IWL_ERR(priv, "Missing ucode owner\n");
		return -ENOMSG;
	}

	owner = nla_get_u8(tb[IWL_TM_ATTR_UCODE_OWNER]);
	if (owner == IWL_OWNERSHIP_DRIVER) {
		priv->ucode_owner = owner;
		iwl_test_enable_notifications(&priv->tst, false);
	} else if (owner == IWL_OWNERSHIP_TM) {
		priv->ucode_owner = owner;
		iwl_test_enable_notifications(&priv->tst, true);
	} else {
		IWL_ERR(priv, "Invalid owner\n");
		return -EINVAL;
	}
	return 0;
}