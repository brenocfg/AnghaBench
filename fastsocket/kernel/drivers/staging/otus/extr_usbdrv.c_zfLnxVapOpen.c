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
typedef  size_t u16_t ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int openFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,size_t,...) ; 
 TYPE_1__* vap ; 
 size_t zfLnxGetVapId (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanEnable (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanSetSSID (struct net_device*,char*,int) ; 

int zfLnxVapOpen(struct net_device *dev)
{
    u16_t vapId;

    vapId = zfLnxGetVapId(dev);

    if (vap[vapId].openFlag == 0)
    {
        vap[vapId].openFlag = 1;
    	printk("zfLnxVapOpen : device name=%s, vap ID=%d\n", dev->name, vapId);
    	zfiWlanSetSSID(dev, "vap1", 4);
    	zfiWlanEnable(dev);
    	netif_start_queue(dev);
    }
    else
    {
        printk("VAP opened error : vap ID=%d\n", vapId);
    }
	return 0;
}