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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ieee802154_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE802154_SUCCESS ; 
 int ieee802154_nl_disassoc_confirm (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fake_disassoc_req(struct net_device *dev,
		struct ieee802154_addr *addr, u8 reason)
{
	return ieee802154_nl_disassoc_confirm(dev, IEEE802154_SUCCESS);
}