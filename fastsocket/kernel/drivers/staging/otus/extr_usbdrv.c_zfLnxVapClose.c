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
typedef  int u16_t ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int openFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 TYPE_1__* vap ; 
 int zfLnxGetVapId (struct net_device*) ; 

int zfLnxVapClose(struct net_device *dev)
{
    u16_t vapId;

    vapId = zfLnxGetVapId(dev);

    if (vapId != 0xffff)
    {
        if (vap[vapId].openFlag == 1)
        {
            printk("zfLnxVapClose: device name=%s, vap ID=%d\n", dev->name, vapId);

            netif_stop_queue(dev);
            vap[vapId].openFlag = 0;
        }
        else
        {
            printk("VAP port was not opened : vap ID=%d\n", vapId);
        }
    }
	return 0;
}