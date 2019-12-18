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
typedef  size_t u32 ;
struct pneigh_entry {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct neigh_table {int key_len; int /*<<< orphan*/ * phash_buckets; } ;

/* Variables and functions */
 struct pneigh_entry* __pneigh_lookup_1 (int /*<<< orphan*/ ,struct net*,void const*,int,struct net_device*) ; 
 size_t pneigh_hash (void const*,int) ; 

struct pneigh_entry *__pneigh_lookup(struct neigh_table *tbl,
		struct net *net, const void *pkey, struct net_device *dev)
{
	int key_len = tbl->key_len;
	u32 hash_val = pneigh_hash(pkey, key_len);

	return __pneigh_lookup_1(tbl->phash_buckets[hash_val],
				 net, pkey, key_len, dev);
}