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
typedef  scalar_t__ u8_t ;
typedef  int u16_t ;
struct TYPE_2__ {int* macAddr; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int zfwGetVapId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanQueryMacAddress(zdev_t* dev, u8_t* addr)
{
    u16_t vapId = 0;
    zmw_get_wlan_dev(dev);

    vapId = zfwGetVapId(dev);

    addr[0] = (u8_t)(wd->macAddr[0] & 0xff);
    addr[1] = (u8_t)(wd->macAddr[0] >> 8);
    addr[2] = (u8_t)(wd->macAddr[1] & 0xff);
    addr[3] = (u8_t)(wd->macAddr[1] >> 8);
    addr[4] = (u8_t)(wd->macAddr[2] & 0xff);
    if (vapId == 0xffff)
        addr[5] = (u8_t)(wd->macAddr[2] >> 8);
    else
    {
#ifdef ZM_VAPMODE_MULTILE_SSID
        addr[5] = (u8_t)(wd->macAddr[2] >> 8); // Multiple SSID
#else
        addr[5] = vapId + 1 + (u8_t)(wd->macAddr[2] >> 8); //VAP
#endif
    }

    return;
}