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
typedef  int u32 ;
struct net_device {int mtu; scalar_t__ type; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 scalar_t__ ARPHRD_IPGRE ; 
 scalar_t__ ARPHRD_LOOPBACK ; 
 scalar_t__ ARPHRD_PPP ; 

__attribute__((used)) static inline __u16 mtu2blksize(struct net_device *dev)
{
	u32 blksize = dev->mtu;
	if (blksize > 0xffff)
		blksize = 0xffff;

	if (dev->type == ARPHRD_ETHER ||
	    dev->type == ARPHRD_PPP ||
	    dev->type == ARPHRD_IPGRE ||
	    dev->type == ARPHRD_LOOPBACK)
		blksize -= 2;

	return (__u16)blksize;
}