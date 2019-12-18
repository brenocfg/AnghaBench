#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dst_entry {int dummy; } ;
struct TYPE_4__ {struct dn_route* dn_next; } ;
struct TYPE_5__ {TYPE_1__ dst; } ;
struct dn_route {TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int dn_rt_hash_mask ; 
 TYPE_3__* dn_rt_hash_table ; 
 int /*<<< orphan*/  dst_free (struct dst_entry*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct dn_route* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dn_run_flush(unsigned long dummy)
{
	int i;
	struct dn_route *rt, *next;

	for(i = 0; i < dn_rt_hash_mask; i++) {
		spin_lock_bh(&dn_rt_hash_table[i].lock);

		if ((rt = xchg(&dn_rt_hash_table[i].chain, NULL)) == NULL)
			goto nothing_to_declare;

		for(; rt; rt=next) {
			next = rt->u.dst.dn_next;
			rt->u.dst.dn_next = NULL;
			dst_free((struct dst_entry *)rt);
		}

nothing_to_declare:
		spin_unlock_bh(&dn_rt_hash_table[i].lock);
	}
}