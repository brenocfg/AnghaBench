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
struct iwl_rxon_context {int dummy; } ;
struct iwl_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_connection_init_rx_config (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int iwlagn_commit_rxon (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int /*<<< orphan*/  iwlagn_set_rxon_chain (struct iwl_priv*,struct iwl_rxon_context*) ; 

__attribute__((used)) static int iwl_set_mode(struct iwl_priv *priv, struct iwl_rxon_context *ctx)
{
	iwl_connection_init_rx_config(priv, ctx);

	iwlagn_set_rxon_chain(priv, ctx);

	return iwlagn_commit_rxon(priv, ctx);
}