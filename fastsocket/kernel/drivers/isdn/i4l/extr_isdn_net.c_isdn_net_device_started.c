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
struct net_device {int dummy; } ;
struct TYPE_4__ {struct net_device* master; } ;
typedef  TYPE_1__ isdn_net_local ;
struct TYPE_5__ {struct net_device* dev; TYPE_1__* local; } ;
typedef  TYPE_2__ isdn_net_dev ;

/* Variables and functions */
 int netif_running (struct net_device*) ; 

__attribute__((used)) static __inline__ int isdn_net_device_started(isdn_net_dev *n)
{
	isdn_net_local *lp = n->local;
	struct net_device *dev;
	
	if (lp->master) 
		dev = lp->master;
	else
		dev = n->dev;
	return netif_running(dev);
}