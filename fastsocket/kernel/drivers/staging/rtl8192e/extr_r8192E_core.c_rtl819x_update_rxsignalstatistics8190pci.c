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
struct TYPE_2__ {int recv_signal_power; } ;
struct r8192_priv {TYPE_1__ stats; } ;
struct ieee80211_rx_stats {int RecvSignalPower; } ;

/* Variables and functions */

__attribute__((used)) static void
rtl819x_update_rxsignalstatistics8190pci(
	struct r8192_priv * priv,
	struct ieee80211_rx_stats * pprevious_stats
	)
{
	int weighting = 0;

	//2 <ToDo> Update Rx Statistics (such as signal strength and signal quality).

	// Initila state
	if(priv->stats.recv_signal_power == 0)
		priv->stats.recv_signal_power = pprevious_stats->RecvSignalPower;

	// To avoid the past result restricting the statistics sensitivity, weight the current power (5/6) to speed up the
	// reaction of smoothed Signal Power.
	if(pprevious_stats->RecvSignalPower > priv->stats.recv_signal_power)
		weighting = 5;
	else if(pprevious_stats->RecvSignalPower < priv->stats.recv_signal_power)
		weighting = (-5);
	//
	// We need more correct power of received packets and the  "SignalStrength" of RxStats have been beautified or translated,
	// so we record the correct power in Dbm here. By Bruce, 2008-03-07.
	//
	priv->stats.recv_signal_power = (priv->stats.recv_signal_power * 5 + pprevious_stats->RecvSignalPower + weighting) / 6;
}