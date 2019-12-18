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
struct sonic_local {int /*<<< orphan*/  dma_bitmode; int /*<<< orphan*/  rra; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int SIZEOF_SONIC_RR ; 
 struct sonic_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sonic_buf_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sonic_rra_put(struct net_device* dev, int entry,
				 int offset, __u16 val)
{
	struct sonic_local *lp = netdev_priv(dev);
	sonic_buf_put(lp->rra, lp->dma_bitmode,
		      (entry * SIZEOF_SONIC_RR) + offset, val);
}