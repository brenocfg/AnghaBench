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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ieee80211_rx_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESG (char*) ; 
 scalar_t__ cmpk_message_handle_rx (struct net_device*,struct ieee80211_rx_stats*) ; 

u32
rtl819xusb_rx_command_packet(
	struct net_device *dev,
	struct ieee80211_rx_stats *pstats
	)
{
	u32	status;

	//RT_TRACE(COMP_RECV, DBG_TRACE, ("---> RxCommandPacketHandle819xUsb()\n"));

	status = cmpk_message_handle_rx(dev, pstats);
	if (status)
	{
		DMESG("rxcommandpackethandle819xusb: It is a command packet\n");
	}
	else
	{
		//RT_TRACE(COMP_RECV, DBG_TRACE, ("RxCommandPacketHandle819xUsb: It is not a command packet\n"));
	}

	//RT_TRACE(COMP_RECV, DBG_TRACE, ("<--- RxCommandPacketHandle819xUsb()\n"));
	return status;
}