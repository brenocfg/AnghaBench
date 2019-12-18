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
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_2__ {int* macAddr; int /*<<< orphan*/  (* zfcbMacAddressNotify ) (int /*<<< orphan*/ *,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int*) ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfCoreMacAddressNotify(zdev_t* dev, u8_t* addr)
{
    zmw_get_wlan_dev(dev);

    wd->macAddr[0] = addr[0] | ((u16_t)addr[1]<<8);
    wd->macAddr[1] = addr[2] | ((u16_t)addr[3]<<8);
    wd->macAddr[2] = addr[4] | ((u16_t)addr[5]<<8);


    //zfHpSetMacAddress(dev, wd->macAddr, 0);
    if (wd->zfcbMacAddressNotify != NULL)
    {
        wd->zfcbMacAddressNotify(dev, addr);
    }
}