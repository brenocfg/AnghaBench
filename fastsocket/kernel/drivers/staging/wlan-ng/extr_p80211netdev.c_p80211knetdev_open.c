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
struct TYPE_5__ {scalar_t__ msdstate; int (* open ) (TYPE_1__*) ;int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; } ;
typedef  TYPE_1__ wlandevice_t ;
struct TYPE_6__ {TYPE_1__* ml_priv; } ;
typedef  TYPE_2__ netdevice_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int /*<<< orphan*/  WLAN_DEVICE_OPEN ; 
 scalar_t__ WLAN_MSD_RUNNING ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static int p80211knetdev_open(netdevice_t *netdev)
{
	int result = 0;		/* success */
	wlandevice_t *wlandev = netdev->ml_priv;

	/* Check to make sure the MSD is running */
	if (wlandev->msdstate != WLAN_MSD_RUNNING)
		return -ENODEV;

	/* Tell the MSD to open */
	if (wlandev->open != NULL) {
		result = wlandev->open(wlandev);
		if (result == 0) {
			netif_start_queue(wlandev->netdev);
			wlandev->state = WLAN_DEVICE_OPEN;
		}
	} else {
		result = -EAGAIN;
	}

	return result;
}