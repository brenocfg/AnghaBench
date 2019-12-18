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
struct iwl_tt_restriction {int is_ht; } ;
struct iwl_tt_mgmt {int state; struct iwl_tt_restriction* restriction; int /*<<< orphan*/  advanced_tt; } ;
struct iwl_priv {struct iwl_tt_mgmt thermal_throttle; } ;

/* Variables and functions */

bool iwl_ht_enabled(struct iwl_priv *priv)
{
	struct iwl_tt_mgmt *tt = &priv->thermal_throttle;
	struct iwl_tt_restriction *restriction;

	if (!priv->thermal_throttle.advanced_tt)
		return true;
	restriction = tt->restriction + tt->state;
	return restriction->is_ht;
}