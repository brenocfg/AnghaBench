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
struct xt_hashlimit_htable {int /*<<< orphan*/  count; } ;
struct dsthash_ent {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashlimit_cachep ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dsthash_ent*) ; 

__attribute__((used)) static inline void
dsthash_free(struct xt_hashlimit_htable *ht, struct dsthash_ent *ent)
{
	hlist_del(&ent->node);
	kmem_cache_free(hashlimit_cachep, ent);
	ht->count--;
}