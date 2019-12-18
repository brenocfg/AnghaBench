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
typedef  int u32 ;
struct hlist_head {int dummy; } ;
struct flow_table {int n_buckets; int /*<<< orphan*/  buckets; int /*<<< orphan*/  hash_seed; } ;

/* Variables and functions */
 struct hlist_head* flex_array_get (int /*<<< orphan*/ ,int) ; 
 int jhash_1word (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hlist_head *find_bucket(struct flow_table *table, u32 hash)
{
	hash = jhash_1word(hash, table->hash_seed);
	return flex_array_get(table->buckets,
				(hash & (table->n_buckets - 1)));
}