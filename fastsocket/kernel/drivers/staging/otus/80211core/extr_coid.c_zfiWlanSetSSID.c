#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
typedef  size_t u16_t ;
struct TYPE_5__ {int ssidLen; TYPE_1__* probingSsidList; scalar_t__* ssid; } ;
struct TYPE_6__ {TYPE_2__ ws; } ;
struct TYPE_4__ {int ssidLen; scalar_t__* ssid; } ;

/* Variables and functions */
 size_t ZM_MAX_PROBE_HIDDEN_SSID_SIZE ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (scalar_t__*,int*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfiWlanSetSSID(zdev_t* dev, u8_t* ssid, u8_t ssidLength)
{
    u16_t i;
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if ( ssidLength <= 32 )
    {
        zmw_enter_critical_section(dev);

        wd->ws.ssidLen = ssidLength;
        zfMemoryCopy(wd->ws.ssid, ssid, ssidLength);

        if ( ssidLength < 32 )
        {
            wd->ws.ssid[ssidLength] = 0;
        }

        wd->ws.probingSsidList[0].ssidLen = ssidLength;
        zfMemoryCopy(wd->ws.probingSsidList[0].ssid, ssid, ssidLength);
        for (i=1; i<ZM_MAX_PROBE_HIDDEN_SSID_SIZE; i++)
        {
            wd->ws.probingSsidList[i].ssidLen = 0;
        }

        zmw_leave_critical_section(dev);
    }
}