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
struct kmem_cache {int dummy; } ;
struct inet_bind_bucket {int /*<<< orphan*/  node; int /*<<< orphan*/  owners; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hlist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_net (struct inet_bind_bucket*) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,struct inet_bind_bucket*) ; 
 int /*<<< orphan*/  release_net (int /*<<< orphan*/ ) ; 

void inet_bind_bucket_destroy(struct kmem_cache *cachep, struct inet_bind_bucket *tb)
{
	if (hlist_empty(&tb->owners)) {
		__hlist_del(&tb->node);
		release_net(ib_net(tb));
		kmem_cache_free(cachep, tb);
	}
}