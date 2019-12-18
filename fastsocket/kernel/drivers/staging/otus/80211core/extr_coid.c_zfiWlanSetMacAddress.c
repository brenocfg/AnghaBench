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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  void* u16_t ;
struct TYPE_2__ {void** macAddr; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfHpSetMacAddress (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetMacAddress(zdev_t* dev, u16_t* mac)
{
    zmw_get_wlan_dev(dev);

    wd->macAddr[0] = mac[0];
    wd->macAddr[1] = mac[1];
    wd->macAddr[2] = mac[2];

    zfHpSetMacAddress(dev, mac, 0);
}