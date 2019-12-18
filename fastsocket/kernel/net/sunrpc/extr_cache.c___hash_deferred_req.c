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
struct cache_head {int dummy; } ;
struct cache_deferred_req {int /*<<< orphan*/  hash; int /*<<< orphan*/  recent; } ;

/* Variables and functions */
 int DFR_HASH (struct cache_head*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cache_defer_hash ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __hash_deferred_req(struct cache_deferred_req *dreq, struct cache_head *item)
{
	int hash = DFR_HASH(item);

	INIT_LIST_HEAD(&dreq->recent);
	hlist_add_head(&dreq->hash, &cache_defer_hash[hash]);
}