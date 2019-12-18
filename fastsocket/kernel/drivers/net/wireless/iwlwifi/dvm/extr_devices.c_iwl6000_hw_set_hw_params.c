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
struct TYPE_2__ {int /*<<< orphan*/ * sens; } ;
struct iwl_priv {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl6000_sensitivity ; 
 int /*<<< orphan*/  iwl6000_set_ct_threshold (struct iwl_priv*) ; 

__attribute__((used)) static void iwl6000_hw_set_hw_params(struct iwl_priv *priv)
{
	iwl6000_set_ct_threshold(priv);

	/* Set initial sensitivity parameters */
	priv->hw_params.sens = &iwl6000_sensitivity;

}