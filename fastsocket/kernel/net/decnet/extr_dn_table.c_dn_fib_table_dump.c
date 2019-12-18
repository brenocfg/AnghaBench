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
struct sk_buff {int len; } ;
struct netlink_callback {int* args; } ;
struct dn_zone {struct dn_zone* dz_next; } ;
struct dn_hash {struct dn_zone* dh_zone_list; } ;
struct dn_fib_table {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dn_fib_tables_lock ; 
 scalar_t__ dn_hash_dump_zone (struct sk_buff*,struct netlink_callback*,struct dn_fib_table*,struct dn_zone*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dn_fib_table_dump(struct dn_fib_table *tb, struct sk_buff *skb,
				struct netlink_callback *cb)
{
	int m, s_m;
	struct dn_zone *dz;
	struct dn_hash *table = (struct dn_hash *)tb->data;

	s_m = cb->args[2];
	read_lock(&dn_fib_tables_lock);
	for(dz = table->dh_zone_list, m = 0; dz; dz = dz->dz_next, m++) {
		if (m < s_m)
			continue;
		if (m > s_m)
			memset(&cb->args[3], 0, sizeof(cb->args) - 3*sizeof(cb->args[0]));

		if (dn_hash_dump_zone(skb, cb, tb, dz) < 0) {
			cb->args[2] = m;
			read_unlock(&dn_fib_tables_lock);
			return -1;
		}
	}
	read_unlock(&dn_fib_tables_lock);
	cb->args[2] = m;

	return skb->len;
}