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
struct jme_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jme_restart_an (struct jme_adapter*) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
jme_nway_reset(struct net_device *netdev)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	jme_restart_an(jme);
	return 0;
}