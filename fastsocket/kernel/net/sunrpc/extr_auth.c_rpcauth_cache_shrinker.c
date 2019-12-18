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
struct shrinker {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cred_unused ; 
 int /*<<< orphan*/  free ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_credcache_lock ; 
 int /*<<< orphan*/  rpcauth_destroy_credlist (int /*<<< orphan*/ *) ; 
 int rpcauth_prune_expired (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rpcauth_cache_shrinker(struct shrinker *shrink, int nr_to_scan, gfp_t gfp_mask)
{
	LIST_HEAD(free);
	int res;

	if ((gfp_mask & GFP_KERNEL) != GFP_KERNEL)
		return (nr_to_scan == 0) ? 0 : -1;
	if (list_empty(&cred_unused))
		return 0;
	spin_lock(&rpc_credcache_lock);
	res = rpcauth_prune_expired(&free, nr_to_scan);
	spin_unlock(&rpc_credcache_lock);
	rpcauth_destroy_credlist(&free);
	return res;
}