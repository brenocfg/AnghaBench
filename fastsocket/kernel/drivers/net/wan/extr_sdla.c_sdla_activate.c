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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ station; } ;
struct frad_local {int /*<<< orphan*/ * dlci; TYPE_1__ config; struct net_device** master; } ;

/* Variables and functions */
 int CONFIG_DLCI_MAX ; 
 int ENODEV ; 
 scalar_t__ FRAD_STATION_NODE ; 
 int /*<<< orphan*/  SDLA_ACTIVATE_DLCI ; 
 int /*<<< orphan*/  abs (int /*<<< orphan*/ ) ; 
 struct frad_local* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  sdla_cmd (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdla_activate(struct net_device *slave, struct net_device *master)
{
	struct frad_local *flp;
	int i;

	flp = netdev_priv(slave);

	for(i=0;i<CONFIG_DLCI_MAX;i++)
		if (flp->master[i] == master)
			break;

	if (i == CONFIG_DLCI_MAX)
		return(-ENODEV);

	flp->dlci[i] = abs(flp->dlci[i]);

	if (netif_running(slave) && (flp->config.station == FRAD_STATION_NODE))
		sdla_cmd(slave, SDLA_ACTIVATE_DLCI, 0, 0, &flp->dlci[i], sizeof(short), NULL, NULL);

	return(0);
}