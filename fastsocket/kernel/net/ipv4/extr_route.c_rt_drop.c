#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rcu_head; } ;
struct TYPE_4__ {TYPE_1__ dst; } ;
struct rtable {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_rcu_free ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 

__attribute__((used)) static inline void rt_drop(struct rtable *rt)
{
	ip_rt_put(rt);
	call_rcu_bh(&rt->u.dst.rcu_head, dst_rcu_free);
}