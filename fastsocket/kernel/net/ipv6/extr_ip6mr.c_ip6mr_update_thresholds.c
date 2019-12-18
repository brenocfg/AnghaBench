#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int maxvif; } ;
struct net {TYPE_1__ ipv6; } ;
struct TYPE_5__ {int minvif; int maxvif; unsigned char* ttls; } ;
struct TYPE_6__ {TYPE_2__ res; } ;
struct mfc6_cache {TYPE_3__ mfc_un; } ;

/* Variables and functions */
 int MAXMIFS ; 
 scalar_t__ MIF_EXISTS (struct net*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 struct net* mfc6_net (struct mfc6_cache*) ; 

__attribute__((used)) static void ip6mr_update_thresholds(struct mfc6_cache *cache, unsigned char *ttls)
{
	int vifi;
	struct net *net = mfc6_net(cache);

	cache->mfc_un.res.minvif = MAXMIFS;
	cache->mfc_un.res.maxvif = 0;
	memset(cache->mfc_un.res.ttls, 255, MAXMIFS);

	for (vifi = 0; vifi < net->ipv6.maxvif; vifi++) {
		if (MIF_EXISTS(net, vifi) &&
		    ttls[vifi] && ttls[vifi] < 255) {
			cache->mfc_un.res.ttls[vifi] = ttls[vifi];
			if (cache->mfc_un.res.minvif > vifi)
				cache->mfc_un.res.minvif = vifi;
			if (cache->mfc_un.res.maxvif <= vifi)
				cache->mfc_un.res.maxvif = vifi + 1;
		}
	}
}