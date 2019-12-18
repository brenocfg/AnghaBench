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
struct il_priv {void** handlers; } ;

/* Variables and functions */
 size_t C_STATS ; 
 size_t C_TX ; 
 size_t N_ALIVE ; 
 size_t N_BEACON ; 
 size_t N_CARD_STATE ; 
 size_t N_CHANNEL_SWITCH ; 
 size_t N_COMPRESSED_BA ; 
 size_t N_ERROR ; 
 size_t N_MISSED_BEACONS ; 
 size_t N_PM_DEBUG_STATS ; 
 size_t N_PM_SLEEP ; 
 size_t N_RX ; 
 size_t N_RX_MPDU ; 
 size_t N_RX_PHY ; 
 size_t N_SPECTRUM_MEASUREMENT ; 
 size_t N_STATS ; 
 void* il4965_hdl_alive ; 
 void* il4965_hdl_beacon ; 
 void* il4965_hdl_c_stats ; 
 void* il4965_hdl_card_state ; 
 void* il4965_hdl_compressed_ba ; 
 void* il4965_hdl_missed_beacon ; 
 void* il4965_hdl_rx ; 
 void* il4965_hdl_rx_phy ; 
 void* il4965_hdl_stats ; 
 void* il4965_hdl_tx ; 
 void* il_hdl_csa ; 
 void* il_hdl_error ; 
 void* il_hdl_pm_debug_stats ; 
 void* il_hdl_pm_sleep ; 
 void* il_hdl_spectrum_measurement ; 
 int /*<<< orphan*/  il_setup_rx_scan_handlers (struct il_priv*) ; 

__attribute__((used)) static void
il4965_setup_handlers(struct il_priv *il)
{
	il->handlers[N_ALIVE] = il4965_hdl_alive;
	il->handlers[N_ERROR] = il_hdl_error;
	il->handlers[N_CHANNEL_SWITCH] = il_hdl_csa;
	il->handlers[N_SPECTRUM_MEASUREMENT] = il_hdl_spectrum_measurement;
	il->handlers[N_PM_SLEEP] = il_hdl_pm_sleep;
	il->handlers[N_PM_DEBUG_STATS] = il_hdl_pm_debug_stats;
	il->handlers[N_BEACON] = il4965_hdl_beacon;

	/*
	 * The same handler is used for both the REPLY to a discrete
	 * stats request from the host as well as for the periodic
	 * stats notifications (after received beacons) from the uCode.
	 */
	il->handlers[C_STATS] = il4965_hdl_c_stats;
	il->handlers[N_STATS] = il4965_hdl_stats;

	il_setup_rx_scan_handlers(il);

	/* status change handler */
	il->handlers[N_CARD_STATE] = il4965_hdl_card_state;

	il->handlers[N_MISSED_BEACONS] = il4965_hdl_missed_beacon;
	/* Rx handlers */
	il->handlers[N_RX_PHY] = il4965_hdl_rx_phy;
	il->handlers[N_RX_MPDU] = il4965_hdl_rx;
	il->handlers[N_RX] = il4965_hdl_rx;
	/* block ack */
	il->handlers[N_COMPRESSED_BA] = il4965_hdl_compressed_ba;
	/* Tx response */
	il->handlers[C_TX] = il4965_hdl_tx;
}