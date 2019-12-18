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
struct vport {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct vport* vport; } ;

/* Variables and functions */
 TYPE_1__* internal_dev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ovs_is_internal_dev (struct net_device*) ; 

struct vport *ovs_internal_dev_get_vport(struct net_device *netdev)
{
	if (!ovs_is_internal_dev(netdev))
		return NULL;

	return internal_dev_priv(netdev)->vport;
}