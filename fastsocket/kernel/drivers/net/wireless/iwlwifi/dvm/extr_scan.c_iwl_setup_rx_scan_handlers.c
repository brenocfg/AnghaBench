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
 size_t REPLY_SCAN_CMD ; 
 size_t SCAN_COMPLETE_NOTIFICATION ; 
 size_t SCAN_RESULTS_NOTIFICATION ; 
 size_t SCAN_START_NOTIFICATION ; 
 int /*<<< orphan*/  iwl_rx_reply_scan ; 
 int /*<<< orphan*/  iwl_rx_scan_complete_notif ; 
 int /*<<< orphan*/  iwl_rx_scan_results_notif ; 
 int /*<<< orphan*/  iwl_rx_scan_start_notif ; 

void iwl_setup_rx_scan_handlers(struct iwl_priv *priv)
{
	/* scan handlers */
	priv->rx_handlers[REPLY_SCAN_CMD] = iwl_rx_reply_scan;
	priv->rx_handlers[SCAN_START_NOTIFICATION] = iwl_rx_scan_start_notif;
	priv->rx_handlers[SCAN_RESULTS_NOTIFICATION] =
					iwl_rx_scan_results_notif;
	priv->rx_handlers[SCAN_COMPLETE_NOTIFICATION] =
					iwl_rx_scan_complete_notif;
}