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
struct net_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; scalar_t__ mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ROSE ; 
 scalar_t__ AX25_BPQ_HEADER_LEN ; 
 scalar_t__ AX25_MAX_HEADER_LEN ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  ROSE_ADDR_LEN ; 
 scalar_t__ ROSE_MAX_PACKET_SIZE ; 
 scalar_t__ ROSE_MIN_LEN ; 
 int /*<<< orphan*/  rose_header_ops ; 
 int /*<<< orphan*/  rose_netdev_ops ; 

void rose_setup(struct net_device *dev)
{
	dev->mtu		= ROSE_MAX_PACKET_SIZE - 2;
	dev->netdev_ops		= &rose_netdev_ops;

	dev->header_ops		= &rose_header_ops;
	dev->hard_header_len	= AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN + ROSE_MIN_LEN;
	dev->addr_len		= ROSE_ADDR_LEN;
	dev->type		= ARPHRD_ROSE;

	/* New-style flags. */
	dev->flags		= IFF_NOARP;
}