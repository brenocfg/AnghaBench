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
struct net_device {int dummy; } ;
struct atalk_route {struct atalk_route* next; struct net_device* dev; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 struct atalk_route* atalk_routes ; 
 int /*<<< orphan*/  atalk_routes_lock ; 
 TYPE_1__ atrtr_default ; 
 int /*<<< orphan*/  atrtr_set_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct atalk_route*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atrtr_device_down(struct net_device *dev)
{
	struct atalk_route **r = &atalk_routes;
	struct atalk_route *tmp;

	write_lock_bh(&atalk_routes_lock);
	while ((tmp = *r) != NULL) {
		if (tmp->dev == dev) {
			*r = tmp->next;
			dev_put(dev);
			kfree(tmp);
		} else
			r = &tmp->next;
	}
	write_unlock_bh(&atalk_routes_lock);

	if (atrtr_default.dev == dev)
		atrtr_set_default(NULL);
}