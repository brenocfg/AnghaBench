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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE802154_MAC_SCAN_ED ; 
 int /*<<< orphan*/  IEEE802154_SUCCESS ; 
 int ieee802154_nl_scan_confirm (struct net_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int fake_scan_req(struct net_device *dev, u8 type, u32 channels,
		u8 page, u8 duration)
{
	u8 edl[27] = {};
	return ieee802154_nl_scan_confirm(dev, IEEE802154_SUCCESS, type,
			channels, page,
			type == IEEE802154_MAC_SCAN_ED ? edl : NULL);
}