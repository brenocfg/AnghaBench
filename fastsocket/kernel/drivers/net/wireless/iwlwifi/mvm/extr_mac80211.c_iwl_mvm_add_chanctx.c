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
struct iwl_mvm_phy_ctxt {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_chanctx_conf {int /*<<< orphan*/  rx_chains_dynamic; int /*<<< orphan*/  rx_chains_static; int /*<<< orphan*/  def; scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int iwl_mvm_phy_ctxt_add (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_add_chanctx(struct ieee80211_hw *hw,
			       struct ieee80211_chanctx_conf *ctx)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_phy_ctxt *phy_ctxt = (void *)ctx->drv_priv;
	int ret;

	mutex_lock(&mvm->mutex);

	IWL_DEBUG_MAC80211(mvm, "Add PHY context\n");
	ret = iwl_mvm_phy_ctxt_add(mvm, phy_ctxt, &ctx->def,
				   ctx->rx_chains_static,
				   ctx->rx_chains_dynamic);
	mutex_unlock(&mvm->mutex);
	return ret;
}