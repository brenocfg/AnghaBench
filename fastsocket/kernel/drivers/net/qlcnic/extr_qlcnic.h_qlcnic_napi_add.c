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
struct qlcnic_adapter {TYPE_1__* nic_ops; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int (* napi_add ) (struct qlcnic_adapter*,struct net_device*) ;} ;

/* Variables and functions */
 int stub1 (struct qlcnic_adapter*,struct net_device*) ; 

__attribute__((used)) static inline int qlcnic_napi_add(struct qlcnic_adapter *adapter,
				  struct net_device *netdev)
{
	return adapter->nic_ops->napi_add(adapter, netdev);
}