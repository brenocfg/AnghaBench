#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  use_rts_for_aggregation; } ;
struct iwl_priv {TYPE_4__* lib; TYPE_3__* cfg; TYPE_1__ hw_params; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_hw_params ) (struct iwl_priv*) ;} ;
struct TYPE_7__ {TYPE_2__* ht_params; } ;
struct TYPE_6__ {int /*<<< orphan*/  use_rts_for_aggregation; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct iwl_priv*) ; 

__attribute__((used)) static void iwl_set_hw_params(struct iwl_priv *priv)
{
	if (priv->cfg->ht_params)
		priv->hw_params.use_rts_for_aggregation =
			priv->cfg->ht_params->use_rts_for_aggregation;

	/* Device-specific setup */
	priv->lib->set_hw_params(priv);
}