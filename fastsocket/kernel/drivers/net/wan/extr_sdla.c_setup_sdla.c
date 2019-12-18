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
struct net_device {int type; int /*<<< orphan*/  mtu; scalar_t__ addr_len; scalar_t__ hard_header_len; scalar_t__ flags; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_2__ {int expires; unsigned long data; int /*<<< orphan*/  function; } ;
struct frad_local {TYPE_1__ timer; int /*<<< orphan*/  dlci_conf; int /*<<< orphan*/  deassoc; int /*<<< orphan*/  assoc; int /*<<< orphan*/  deactivate; int /*<<< orphan*/  activate; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDLA_MAX_MTU ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_boot_setup_check (struct net_device*) ; 
 struct frad_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sdla_activate ; 
 int /*<<< orphan*/  sdla_assoc ; 
 int /*<<< orphan*/  sdla_deactivate ; 
 int /*<<< orphan*/  sdla_deassoc ; 
 int /*<<< orphan*/  sdla_dlci_conf ; 
 int /*<<< orphan*/  sdla_netdev_ops ; 
 int /*<<< orphan*/  sdla_poll ; 

__attribute__((used)) static void setup_sdla(struct net_device *dev)
{
	struct frad_local *flp = netdev_priv(dev);

	netdev_boot_setup_check(dev);

	dev->netdev_ops		= &sdla_netdev_ops;
	dev->flags		= 0;
	dev->type		= 0xFFFF;
	dev->hard_header_len	= 0;
	dev->addr_len		= 0;
	dev->mtu		= SDLA_MAX_MTU;

	flp->activate		= sdla_activate;
	flp->deactivate		= sdla_deactivate;
	flp->assoc		= sdla_assoc;
	flp->deassoc		= sdla_deassoc;
	flp->dlci_conf		= sdla_dlci_conf;

	init_timer(&flp->timer);
	flp->timer.expires	= 1;
	flp->timer.data		= (unsigned long) dev;
	flp->timer.function	= sdla_poll;
}