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
struct TYPE_2__ {int /*<<< orphan*/  ct_kill_exit_threshold; int /*<<< orphan*/  ct_kill_threshold; } ;
struct iwl_priv {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_KILL_EXIT_THRESHOLD ; 
 int /*<<< orphan*/  CT_KILL_THRESHOLD_LEGACY ; 

__attribute__((used)) static void iwl1000_set_ct_threshold(struct iwl_priv *priv)
{
	/* want Celsius */
	priv->hw_params.ct_kill_threshold = CT_KILL_THRESHOLD_LEGACY;
	priv->hw_params.ct_kill_exit_threshold = CT_KILL_EXIT_THRESHOLD;
}