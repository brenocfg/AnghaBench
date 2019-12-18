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
struct dst_ops {int dummy; } ;
struct TYPE_4__ {unsigned long lastuse; struct dn_route* dn_next; int /*<<< orphan*/  __refcnt; } ;
struct TYPE_5__ {TYPE_1__ dst; } ;
struct dn_route {TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; struct dn_route* chain; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int dn_rt_hash_mask ; 
 TYPE_3__* dn_rt_hash_table ; 
 int /*<<< orphan*/  dnrt_drop (struct dn_route*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dn_dst_gc(struct dst_ops *ops)
{
	struct dn_route *rt, **rtp;
	int i;
	unsigned long now = jiffies;
	unsigned long expire = 10 * HZ;

	for(i = 0; i <= dn_rt_hash_mask; i++) {

		spin_lock_bh(&dn_rt_hash_table[i].lock);
		rtp = &dn_rt_hash_table[i].chain;

		while((rt=*rtp) != NULL) {
			if (atomic_read(&rt->u.dst.__refcnt) ||
					(now - rt->u.dst.lastuse) < expire) {
				rtp = &rt->u.dst.dn_next;
				continue;
			}
			*rtp = rt->u.dst.dn_next;
			rt->u.dst.dn_next = NULL;
			dnrt_drop(rt);
			break;
		}
		spin_unlock_bh(&dn_rt_hash_table[i].lock);
	}

	return 0;
}