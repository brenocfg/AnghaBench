#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_10__ {TYPE_4__* qs; } ;
struct TYPE_7__ {TYPE_1__* qset; } ;
struct TYPE_8__ {TYPE_2__ sge; } ;
struct adapter {TYPE_5__ sge; TYPE_3__ params; } ;
struct TYPE_9__ {int lro_enabled; } ;
struct TYPE_6__ {int lro; } ;

/* Variables and functions */
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void set_qset_lro(struct net_device *dev, int qset_idx, int val)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;

	adapter->params.sge.qset[qset_idx].lro = !!val;
	adapter->sge.qs[qset_idx].lro_enabled = !!val;
}