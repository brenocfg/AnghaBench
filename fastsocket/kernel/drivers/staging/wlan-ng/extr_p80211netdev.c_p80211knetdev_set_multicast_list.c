#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* set_multicast_list ) (TYPE_1__*,TYPE_2__*) ;} ;
typedef  TYPE_1__ wlandevice_t ;
struct TYPE_7__ {TYPE_1__* ml_priv; } ;
typedef  TYPE_2__ netdevice_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void p80211knetdev_set_multicast_list(netdevice_t *dev)
{
	wlandevice_t *wlandev = dev->ml_priv;

	/* TODO:  real multicast support as well */

	if (wlandev->set_multicast_list)
		wlandev->set_multicast_list(wlandev, dev);

}