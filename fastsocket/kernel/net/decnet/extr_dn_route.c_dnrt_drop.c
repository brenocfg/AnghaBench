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
struct TYPE_4__ {int /*<<< orphan*/  rcu_head; } ;
struct TYPE_3__ {TYPE_2__ dst; } ;
struct dn_route {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_rcu_free ; 
 int /*<<< orphan*/  dst_release (TYPE_2__*) ; 

__attribute__((used)) static inline void dnrt_drop(struct dn_route *rt)
{
	dst_release(&rt->u.dst);
	call_rcu_bh(&rt->u.dst.rcu_head, dst_rcu_free);
}