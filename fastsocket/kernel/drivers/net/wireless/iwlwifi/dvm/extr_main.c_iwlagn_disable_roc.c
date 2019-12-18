#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  node_addr; int /*<<< orphan*/  filter_flags; int /*<<< orphan*/  dev_type; } ;
struct iwl_rxon_context {int is_active; TYPE_1__ staging; } ;
struct iwl_priv {int hw_roc_setup; int /*<<< orphan*/ * hw_roc_channel; int /*<<< orphan*/  mutex; struct iwl_rxon_context* contexts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 size_t IWL_RXON_CTX_PAN ; 
 int /*<<< orphan*/  RXON_DEV_TYPE_P2P ; 
 int /*<<< orphan*/  RXON_FILTER_ASSOC_MSK ; 
 int /*<<< orphan*/  iwlagn_commit_rxon (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iwlagn_disable_roc(struct iwl_priv *priv)
{
	struct iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_PAN];

	lockdep_assert_held(&priv->mutex);

	if (!priv->hw_roc_setup)
		return;

	ctx->staging.dev_type = RXON_DEV_TYPE_P2P;
	ctx->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;

	priv->hw_roc_channel = NULL;

	memset(ctx->staging.node_addr, 0, ETH_ALEN);

	iwlagn_commit_rxon(priv, ctx);

	ctx->is_active = false;
	priv->hw_roc_setup = false;
}