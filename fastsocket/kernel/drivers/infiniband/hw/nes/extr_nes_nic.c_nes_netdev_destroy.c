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
struct nes_vnic {int /*<<< orphan*/  nesibdev; scalar_t__ of_device_registered; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_destroy_ofa_device (int /*<<< orphan*/ ) ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 

void nes_netdev_destroy(struct net_device *netdev)
{
	struct nes_vnic *nesvnic = netdev_priv(netdev);

	/* make sure 'stop' method is called by Linux stack */
	/* nes_netdev_stop(netdev); */

	list_del(&nesvnic->list);

	if (nesvnic->of_device_registered) {
		nes_destroy_ofa_device(nesvnic->nesibdev);
	}

	free_netdev(netdev);
}