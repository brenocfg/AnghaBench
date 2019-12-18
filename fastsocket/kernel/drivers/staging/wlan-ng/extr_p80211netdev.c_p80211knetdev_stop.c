#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* close ) (TYPE_1__*) ;int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; } ;
typedef  TYPE_1__ wlandevice_t ;
struct TYPE_6__ {TYPE_1__* ml_priv; } ;
typedef  TYPE_2__ netdevice_t ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_DEVICE_CLOSED ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static int p80211knetdev_stop(netdevice_t *netdev)
{
	int result = 0;
	wlandevice_t *wlandev = netdev->ml_priv;

	if (wlandev->close != NULL)
		result = wlandev->close(wlandev);

	netif_stop_queue(wlandev->netdev);
	wlandev->state = WLAN_DEVICE_CLOSED;

	return result;
}