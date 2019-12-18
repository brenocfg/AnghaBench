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
struct port_info {unsigned int iscsi_ipv4addr; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline unsigned int cxgb3i_get_private_ipv4addr(struct net_device *ndev)
{
	return ((struct port_info *)(netdev_priv(ndev)))->iscsi_ipv4addr;
}