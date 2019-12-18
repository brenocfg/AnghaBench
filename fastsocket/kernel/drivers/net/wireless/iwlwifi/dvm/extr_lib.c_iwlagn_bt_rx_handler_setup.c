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
struct iwl_priv {int /*<<< orphan*/ * rx_handlers; } ;

/* Variables and functions */
 size_t REPLY_BT_COEX_PROFILE_NOTIF ; 
 int /*<<< orphan*/  iwlagn_bt_coex_profile_notif ; 

void iwlagn_bt_rx_handler_setup(struct iwl_priv *priv)
{
	priv->rx_handlers[REPLY_BT_COEX_PROFILE_NOTIF] =
		iwlagn_bt_coex_profile_notif;
}