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
struct usbdrv_private {int /*<<< orphan*/  hbTimer10ms; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zfiHeartBeat (struct net_device*) ; 

void zfLnx10msTimer(struct net_device* dev)
{
    struct usbdrv_private *macp = dev->ml_priv;

    mod_timer(&(macp->hbTimer10ms), jiffies + (1*HZ)/100);   //10 ms
    zfiHeartBeat(dev);
    return;
}