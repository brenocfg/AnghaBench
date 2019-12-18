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
struct nic {int /*<<< orphan*/  (* mdio_ctrl ) (struct nic*,int,int /*<<< orphan*/ ,int,int) ;} ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdi_write ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct nic*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mdio_write(struct net_device *netdev, int addr, int reg, int data)
{
	struct nic *nic = netdev_priv(netdev);

	nic->mdio_ctrl(nic, addr, mdi_write, reg, data);
}