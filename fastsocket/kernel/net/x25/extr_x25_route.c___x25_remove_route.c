#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ next; } ;
struct x25_route {TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (TYPE_1__*) ; 
 int /*<<< orphan*/  x25_route_put (struct x25_route*) ; 

__attribute__((used)) static void __x25_remove_route(struct x25_route *rt)
{
	if (rt->node.next) {
		list_del(&rt->node);
		x25_route_put(rt);
	}
}