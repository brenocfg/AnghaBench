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
struct agp_bridge_data {TYPE_1__* driver; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  agp_backend_cleanup (struct agp_bridge_data*) ; 
 int /*<<< orphan*/  agp_bridges ; 
 int /*<<< orphan*/  agp_frontend_cleanup () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

void agp_remove_bridge(struct agp_bridge_data *bridge)
{
	agp_backend_cleanup(bridge);
	list_del(&bridge->list);
	if (list_empty(&agp_bridges))
		agp_frontend_cleanup();
	module_put(bridge->driver->owner);
}