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
typedef  void* u8 ;
struct wpan_phy {int /*<<< orphan*/  pib_lock; void* current_page; void* current_channel; } ;
struct net_device {int dummy; } ;
struct ieee802154_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE802154_SUCCESS ; 
 int /*<<< orphan*/  fake_get_short_addr (struct net_device*) ; 
 int ieee802154_nl_assoc_confirm (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wpan_phy* net_to_phy (struct net_device*) ; 

__attribute__((used)) static int fake_assoc_req(struct net_device *dev,
		struct ieee802154_addr *addr, u8 channel, u8 page, u8 cap)
{
	struct wpan_phy *phy = net_to_phy(dev);

	mutex_lock(&phy->pib_lock);
	phy->current_channel = channel;
	phy->current_page = page;
	mutex_unlock(&phy->pib_lock);

	/* We simply emulate it here */
	return ieee802154_nl_assoc_confirm(dev, fake_get_short_addr(dev),
			IEEE802154_SUCCESS);
}