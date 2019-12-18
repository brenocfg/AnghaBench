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
struct TYPE_2__ {struct mfc6_cache** mfc6_cache_array; } ;
struct net {TYPE_1__ ipv6; } ;
struct mfc6_cache {int /*<<< orphan*/  mf6c_mcastgrp; int /*<<< orphan*/  mf6c_origin; struct mfc6_cache* next; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int MFC6_HASH (struct in6_addr*,struct in6_addr*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr*) ; 

__attribute__((used)) static struct mfc6_cache *ip6mr_cache_find(struct net *net,
					   struct in6_addr *origin,
					   struct in6_addr *mcastgrp)
{
	int line = MFC6_HASH(mcastgrp, origin);
	struct mfc6_cache *c;

	for (c = net->ipv6.mfc6_cache_array[line]; c; c = c->next) {
		if (ipv6_addr_equal(&c->mf6c_origin, origin) &&
		    ipv6_addr_equal(&c->mf6c_mcastgrp, mcastgrp))
			break;
	}
	return c;
}