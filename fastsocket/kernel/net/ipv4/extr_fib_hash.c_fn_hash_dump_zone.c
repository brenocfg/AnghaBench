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
struct fn_zone {int fz_divisor; int /*<<< orphan*/ * fz_hash; } ;
struct fib_table {int dummy; } ;

/* Variables and functions */
 scalar_t__ fn_hash_dump_bucket (struct sk_buff*,struct netlink_callback*,struct fib_table*,struct fn_zone*,int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
fn_hash_dump_zone(struct sk_buff *skb, struct netlink_callback *cb,
		   struct fib_table *tb,
		   struct fn_zone *fz)
{
	int h, s_h;

	if (fz->fz_hash == NULL)
		return skb->len;
	s_h = cb->args[3];
	for (h = s_h; h < fz->fz_divisor; h++) {
		if (hlist_empty(&fz->fz_hash[h]))
			continue;
		if (fn_hash_dump_bucket(skb, cb, tb, fz, &fz->fz_hash[h]) < 0) {
			cb->args[3] = h;
			return -1;
		}
		memset(&cb->args[4], 0,
		       sizeof(cb->args) - 4*sizeof(cb->args[0]));
	}
	cb->args[3] = h;
	return skb->len;
}