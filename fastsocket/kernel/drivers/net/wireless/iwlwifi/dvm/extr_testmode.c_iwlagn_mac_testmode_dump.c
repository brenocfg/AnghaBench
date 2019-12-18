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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {scalar_t__* args; } ;
struct iwl_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  tst; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 size_t IWL_TM_ATTR_COMMAND ; 
 int IWL_TM_ATTR_MAX ; 
 int iwl_test_dump (int /*<<< orphan*/ *,scalar_t__,struct sk_buff*,struct netlink_callback*) ; 
 int iwl_test_parse (int /*<<< orphan*/ *,struct nlattr**,void*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 

int iwlagn_mac_testmode_dump(struct ieee80211_hw *hw, struct sk_buff *skb,
		      struct netlink_callback *cb,
		      void *data, int len)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	int result;
	u32 cmd;

	if (cb->args[3]) {
		/* offset by 1 since commands start at 0 */
		cmd = cb->args[3] - 1;
	} else {
		struct nlattr *tb[IWL_TM_ATTR_MAX];

		result = iwl_test_parse(&priv->tst, tb, data, len);
		if (result)
			return result;

		cmd = nla_get_u32(tb[IWL_TM_ATTR_COMMAND]);
		cb->args[3] = cmd + 1;
	}

	/* in case multiple accesses to the device happens */
	mutex_lock(&priv->mutex);
	result = iwl_test_dump(&priv->tst, cmd, skb, cb);
	mutex_unlock(&priv->mutex);
	return result;
}