#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* netdev; scalar_t__ master; } ;
typedef  TYPE_2__ isdn_net_local ;
struct TYPE_4__ {scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_stop_queue (scalar_t__) ; 

__attribute__((used)) static __inline__ void isdn_net_device_stop_queue(isdn_net_local *lp)
{
	if (lp->master)
		netif_stop_queue(lp->master);
	else
		netif_stop_queue(lp->netdev->dev);
}