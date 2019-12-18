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
struct TYPE_2__ {scalar_t__ AdapterRAMPtr; int /*<<< orphan*/  BurnedInAddrPtr; } ;
struct net_local {TYPE_1__ intptrs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_INT_PTRS ; 
 int be16_to_cpu (unsigned short) ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned short) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tms380tr_read_ram (struct net_device*,unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tms380tr_read_ptr(struct net_device *dev)
{
	struct net_local *tp = netdev_priv(dev);
	unsigned short adapterram;

	tms380tr_read_ram(dev, (unsigned char *)&tp->intptrs.BurnedInAddrPtr,
			ADAPTER_INT_PTRS, 16);
	tms380tr_read_ram(dev, (unsigned char *)&adapterram,
			cpu_to_be16((unsigned short)tp->intptrs.AdapterRAMPtr), 2);
	return be16_to_cpu(adapterram); 
}