#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct hh_cache {int dummy; } ;
struct TYPE_3__ {scalar_t__ p_encap; } ;
typedef  TYPE_1__ isdn_net_local ;

/* Variables and functions */
 scalar_t__ ISDN_NET_ENCAP_ETHER ; 
 int /*<<< orphan*/  eth_header_cache_update (struct hh_cache*,struct net_device const*,unsigned char const*) ; 
 TYPE_1__* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static void isdn_header_cache_update(struct hh_cache *hh,
				     const struct net_device *dev,
				     const unsigned char *haddr)
{
	isdn_net_local *lp = netdev_priv(dev);
	if (lp->p_encap == ISDN_NET_ENCAP_ETHER)
		eth_header_cache_update(hh, dev, haddr);
}