#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* digipeat; struct TYPE_4__* next; struct net_device* dev; } ;
typedef  TYPE_1__ ax25_route ;

/* Variables and functions */
 TYPE_1__* ax25_route_list ; 
 int /*<<< orphan*/  ax25_route_lock ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void ax25_rt_device_down(struct net_device *dev)
{
	ax25_route *s, *t, *ax25_rt;

	write_lock_bh(&ax25_route_lock);
	ax25_rt = ax25_route_list;
	while (ax25_rt != NULL) {
		s       = ax25_rt;
		ax25_rt = ax25_rt->next;

		if (s->dev == dev) {
			if (ax25_route_list == s) {
				ax25_route_list = s->next;
				kfree(s->digipeat);
				kfree(s);
			} else {
				for (t = ax25_route_list; t != NULL; t = t->next) {
					if (t->next == s) {
						t->next = s->next;
						kfree(s->digipeat);
						kfree(s);
						break;
					}
				}
			}
		}
	}
	write_unlock_bh(&ax25_route_lock);
}