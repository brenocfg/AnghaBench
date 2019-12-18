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
struct dn_ifaddr {TYPE_1__* ifa_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ * ifa_list; } ;

/* Variables and functions */
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dn_fib_add_ifaddr (struct dn_ifaddr*) ; 
 int /*<<< orphan*/  dn_fib_del_ifaddr (struct dn_ifaddr*) ; 
 int /*<<< orphan*/  dn_fib_disable_addr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dn_fib_sync_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_rt_cache_flush (int) ; 

__attribute__((used)) static int dn_fib_dnaddr_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct dn_ifaddr *ifa = (struct dn_ifaddr *)ptr;

	switch(event) {
		case NETDEV_UP:
			dn_fib_add_ifaddr(ifa);
			dn_fib_sync_up(ifa->ifa_dev->dev);
			dn_rt_cache_flush(-1);
			break;
		case NETDEV_DOWN:
			dn_fib_del_ifaddr(ifa);
			if (ifa->ifa_dev && ifa->ifa_dev->ifa_list == NULL) {
				dn_fib_disable_addr(ifa->ifa_dev->dev, 1);
			} else {
				dn_rt_cache_flush(-1);
			}
			break;
	}
	return NOTIFY_DONE;
}