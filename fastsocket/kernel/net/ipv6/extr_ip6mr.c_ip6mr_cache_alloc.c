#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  minvif; } ;
struct TYPE_4__ {TYPE_1__ res; } ;
struct mfc6_cache {TYPE_2__ mfc_un; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAXMIFS ; 
 struct mfc6_cache* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc6_net_set (struct mfc6_cache*,struct net*) ; 
 int /*<<< orphan*/  mrt_cachep ; 

__attribute__((used)) static struct mfc6_cache *ip6mr_cache_alloc(struct net *net)
{
	struct mfc6_cache *c = kmem_cache_zalloc(mrt_cachep, GFP_KERNEL);
	if (c == NULL)
		return NULL;
	c->mfc_un.res.minvif = MAXMIFS;
	mfc6_net_set(c, net);
	return c;
}