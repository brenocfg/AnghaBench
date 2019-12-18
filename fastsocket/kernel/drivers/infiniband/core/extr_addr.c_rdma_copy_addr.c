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
struct rdma_dev_addr {int /*<<< orphan*/  bound_dev_if; int /*<<< orphan*/  dst_dev_addr; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  src_dev_addr; int /*<<< orphan*/  dev_type; } ;
struct net_device {unsigned char const* dev_addr; unsigned char const* broadcast; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_ADDR_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 

int rdma_copy_addr(struct rdma_dev_addr *dev_addr, struct net_device *dev,
		     const unsigned char *dst_dev_addr)
{
	dev_addr->dev_type = dev->type;
	memcpy(dev_addr->src_dev_addr, dev->dev_addr, MAX_ADDR_LEN);
	memcpy(dev_addr->broadcast, dev->broadcast, MAX_ADDR_LEN);
	if (dst_dev_addr)
		memcpy(dev_addr->dst_dev_addr, dst_dev_addr, MAX_ADDR_LEN);
	dev_addr->bound_dev_if = dev->ifindex;
	return 0;
}