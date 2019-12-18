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
struct net_device {int dummy; } ;
struct adapter {int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 scalar_t__ A_SGE_CTXT_CMD ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int t4_fwaddrspace_write (struct adapter*,int /*<<< orphan*/ ,scalar_t__,int) ; 

int cxgb4_flush_eq_cache(struct net_device *dev)
{
	struct adapter *adap = netdev2adap(dev);
	int ret;

	ret = t4_fwaddrspace_write(adap, adap->mbox,
				   0xe1000000 + A_SGE_CTXT_CMD, 0x20000000);
	return ret;
}