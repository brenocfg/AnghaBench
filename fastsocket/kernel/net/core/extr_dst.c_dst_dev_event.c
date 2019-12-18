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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct dst_entry {struct dst_entry* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct dst_entry* list; } ;

/* Variables and functions */
#define  NETDEV_DOWN 129 
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_DONE ; 
 struct dst_entry* dst_busy_list ; 
 TYPE_1__ dst_garbage ; 
 int /*<<< orphan*/  dst_gc_mutex ; 
 int /*<<< orphan*/  dst_ifdown (struct dst_entry*,struct net_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dst_dev_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = ptr;
	struct dst_entry *dst, *last = NULL;

	switch (event) {
	case NETDEV_UNREGISTER:
	case NETDEV_DOWN:
		mutex_lock(&dst_gc_mutex);
		for (dst = dst_busy_list; dst; dst = dst->next) {
			last = dst;
			dst_ifdown(dst, dev, event != NETDEV_DOWN);
		}

		spin_lock_bh(&dst_garbage.lock);
		dst = dst_garbage.list;
		dst_garbage.list = NULL;
		spin_unlock_bh(&dst_garbage.lock);

		if (last)
			last->next = dst;
		else
			dst_busy_list = dst;
		for (; dst; dst = dst->next) {
			dst_ifdown(dst, dev, event != NETDEV_DOWN);
		}
		mutex_unlock(&dst_gc_mutex);
		break;
	}
	return NOTIFY_DONE;
}