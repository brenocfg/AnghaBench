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
struct TYPE_2__ {int /*<<< orphan*/  advanced_tt; } ;
struct iwl_priv {scalar_t__ temperature; TYPE_1__ thermal_throttle; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ CT_KILL_THRESHOLD ; 
 scalar_t__ CT_KILL_THRESHOLD_LEGACY ; 
 scalar_t__ IWL_TT_CT_KILL_MARGIN ; 

__attribute__((used)) static bool iwl_within_ct_kill_margin(struct iwl_priv *priv)
{
	s32 temp = priv->temperature; /* degrees CELSIUS except specified */
	bool within_margin = false;

	if (!priv->thermal_throttle.advanced_tt)
		within_margin = ((temp + IWL_TT_CT_KILL_MARGIN) >=
				CT_KILL_THRESHOLD_LEGACY) ? true : false;
	else
		within_margin = ((temp + IWL_TT_CT_KILL_MARGIN) >=
				CT_KILL_THRESHOLD) ? true : false;
	return within_margin;
}