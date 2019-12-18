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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_rxon_context {int dummy; } ;
struct iwl_priv {int dummy; } ;
struct iwl_link_quality_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  iwl_sta_fill_lq (struct iwl_priv*,struct iwl_rxon_context*,int /*<<< orphan*/ ,struct iwl_link_quality_cmd*) ; 
 struct iwl_link_quality_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iwl_link_quality_cmd *
iwl_sta_alloc_lq(struct iwl_priv *priv, struct iwl_rxon_context *ctx,
		 u8 sta_id)
{
	struct iwl_link_quality_cmd *link_cmd;

	link_cmd = kzalloc(sizeof(struct iwl_link_quality_cmd), GFP_KERNEL);
	if (!link_cmd) {
		IWL_ERR(priv, "Unable to allocate memory for LQ cmd.\n");
		return NULL;
	}

	iwl_sta_fill_lq(priv, ctx, sta_id, link_cmd);

	return link_cmd;
}