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
struct sk_buff {scalar_t__ data; } ;
struct rxdone_entry_desc {int dev_flags; int /*<<< orphan*/  rssi; } ;
struct link_ant {void* rssi_ant; } ;
struct link_qual {int /*<<< orphan*/  rx_success; } ;
struct link {void* avg_rssi; struct link_ant ant; struct link_qual qual; } ;
struct rt2x00_dev {int /*<<< orphan*/  intf_sta_count; struct link link; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 void* MOVING_AVERAGE (void*,int /*<<< orphan*/ ) ; 
 int RXDONE_MY_BSS ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 

void rt2x00link_update_stats(struct rt2x00_dev *rt2x00dev,
			     struct sk_buff *skb,
			     struct rxdone_entry_desc *rxdesc)
{
	struct link *link = &rt2x00dev->link;
	struct link_qual *qual = &rt2x00dev->link.qual;
	struct link_ant *ant = &rt2x00dev->link.ant;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;

	/*
	 * No need to update the stats for !=STA interfaces
	 */
	if (!rt2x00dev->intf_sta_count)
		return;

	/*
	 * Frame was received successfully since non-succesfull
	 * frames would have been dropped by the hardware.
	 */
	qual->rx_success++;

	/*
	 * We are only interested in quality statistics from
	 * beacons which came from the BSS which we are
	 * associated with.
	 */
	if (!ieee80211_is_beacon(hdr->frame_control) ||
	    !(rxdesc->dev_flags & RXDONE_MY_BSS))
		return;

	/*
	 * Update global RSSI
	 */
	link->avg_rssi = MOVING_AVERAGE(link->avg_rssi, rxdesc->rssi);

	/*
	 * Update antenna RSSI
	 */
	ant->rssi_ant = MOVING_AVERAGE(ant->rssi_ant, rxdesc->rssi);
}