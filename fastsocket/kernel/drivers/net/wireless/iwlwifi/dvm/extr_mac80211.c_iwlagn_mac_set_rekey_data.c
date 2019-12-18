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
struct iwl_priv {int have_rekey_data; int /*<<< orphan*/  mutex; int /*<<< orphan*/  replay_ctr; int /*<<< orphan*/  kck; int /*<<< orphan*/  kek; TYPE_1__* contexts; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct cfg80211_gtk_rekey_data {int /*<<< orphan*/  replay_ctr; int /*<<< orphan*/  kck; int /*<<< orphan*/  kek; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_4__ {scalar_t__ sw_crypto; } ;
struct TYPE_3__ {struct ieee80211_vif* vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 size_t IWL_RXON_CTX_BSS ; 
 int /*<<< orphan*/  NL80211_KCK_LEN ; 
 int /*<<< orphan*/  NL80211_KEK_LEN ; 
 int /*<<< orphan*/  be64_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 TYPE_2__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwlagn_mac_set_rekey_data(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct cfg80211_gtk_rekey_data *data)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	if (iwlwifi_mod_params.sw_crypto)
		return;

	IWL_DEBUG_MAC80211(priv, "enter\n");
	mutex_lock(&priv->mutex);

	if (priv->contexts[IWL_RXON_CTX_BSS].vif != vif)
		goto out;

	memcpy(priv->kek, data->kek, NL80211_KEK_LEN);
	memcpy(priv->kck, data->kck, NL80211_KCK_LEN);
	priv->replay_ctr =
		cpu_to_le64(be64_to_cpup((__be64 *)&data->replay_ctr));
	priv->have_rekey_data = true;

 out:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");
}