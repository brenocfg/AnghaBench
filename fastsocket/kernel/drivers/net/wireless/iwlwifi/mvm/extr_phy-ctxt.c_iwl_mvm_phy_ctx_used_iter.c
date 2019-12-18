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
struct phy_ctx_used_data {int /*<<< orphan*/  used; } ;
struct iwl_mvm_phy_ctxt {int /*<<< orphan*/  id; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_chanctx_conf {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_phy_ctx_used_iter(struct ieee80211_hw *hw,
				      struct ieee80211_chanctx_conf *ctx,
				      void *_data)
{
	struct phy_ctx_used_data *data = _data;
	struct iwl_mvm_phy_ctxt *phy_ctxt = (void *)ctx->drv_priv;

	__set_bit(phy_ctxt->id, data->used);
}