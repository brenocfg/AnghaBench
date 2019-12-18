#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int flags; int /*<<< orphan*/  addr_len; scalar_t__ dev_addr; } ;
typedef  int /*<<< orphan*/  rose_address ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rose_add_loopback_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rose_del_loopback_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rose_set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr *sa = addr;
	int err;

	if (!memcpy(dev->dev_addr, sa->sa_data, dev->addr_len))
		return 0;

	if (dev->flags & IFF_UP) {
		err = rose_add_loopback_node((rose_address *)dev->dev_addr);
		if (err)
			return err;

		rose_del_loopback_node((rose_address *)dev->dev_addr);
	}

	memcpy(dev->dev_addr, sa->sa_data, dev->addr_len);

	return 0;
}