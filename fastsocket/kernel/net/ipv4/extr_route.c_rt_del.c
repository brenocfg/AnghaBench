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
struct TYPE_4__ {struct rtable* rt_next; } ;
struct TYPE_5__ {TYPE_1__ dst; } ;
struct rtable {TYPE_2__ u; } ;
struct TYPE_6__ {struct rtable* chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  rt_free (struct rtable*) ; 
 int /*<<< orphan*/  rt_hash_lock_addr (unsigned int) ; 
 TYPE_3__* rt_hash_table ; 
 scalar_t__ rt_is_expired (struct rtable*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt_del(unsigned hash, struct rtable *rt)
{
	struct rtable **rthp, *aux;

	rthp = &rt_hash_table[hash].chain;
	spin_lock_bh(rt_hash_lock_addr(hash));
	ip_rt_put(rt);
	while ((aux = *rthp) != NULL) {
		if (aux == rt || rt_is_expired(aux)) {
			*rthp = aux->u.dst.rt_next;
			rt_free(aux);
			continue;
		}
		rthp = &aux->u.dst.rt_next;
	}
	spin_unlock_bh(rt_hash_lock_addr(hash));
}