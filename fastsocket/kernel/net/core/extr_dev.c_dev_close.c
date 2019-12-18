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
struct net_device {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  unreg_list; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_close_many (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 
 int /*<<< orphan*/  single ; 

int dev_close(struct net_device *dev)
{
	if (dev->flags & IFF_UP) {
		LIST_HEAD(single);
		list_add(&netdev_extended(dev)->unreg_list, &single);
		dev_close_many(&single);
		list_del(&single);
	}
	return 0;
}