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
struct iwl_tt_restriction {int rx_stream; } ;
struct iwl_tt_mgmt {int state; struct iwl_tt_restriction* restriction; int /*<<< orphan*/  advanced_tt; } ;
struct iwl_priv {struct iwl_tt_mgmt thermal_throttle; } ;
typedef  enum iwl_antenna_ok { ____Placeholder_iwl_antenna_ok } iwl_antenna_ok ;

/* Variables and functions */
 int IWL_ANT_OK_MULTI ; 

enum iwl_antenna_ok iwl_rx_ant_restriction(struct iwl_priv *priv)
{
	struct iwl_tt_mgmt *tt = &priv->thermal_throttle;
	struct iwl_tt_restriction *restriction;

	if (!priv->thermal_throttle.advanced_tt)
		return IWL_ANT_OK_MULTI;
	restriction = tt->restriction + tt->state;
	return restriction->rx_stream;
}