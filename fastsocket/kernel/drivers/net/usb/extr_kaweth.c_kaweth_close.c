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
struct kaweth_device {int /*<<< orphan*/  intf; int /*<<< orphan*/  status; scalar_t__ opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  KAWETH_STATUS_CLOSING ; 
 int /*<<< orphan*/  kaweth_kill_urbs (struct kaweth_device*) ; 
 struct kaweth_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  usb_autopm_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kaweth_close(struct net_device *net)
{
	struct kaweth_device *kaweth = netdev_priv(net);

	netif_stop_queue(net);
	kaweth->opened = 0;

	kaweth->status |= KAWETH_STATUS_CLOSING;

	kaweth_kill_urbs(kaweth);

	kaweth->status &= ~KAWETH_STATUS_CLOSING;

	usb_autopm_enable(kaweth->intf);

	return 0;
}