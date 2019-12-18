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
typedef  size_t u8_t ;
typedef  scalar_t__ u32_t ;
typedef  int u16_t ;
struct TYPE_4__ {int** macAddr; int wdsBitmap; size_t* encryMode; } ;
struct TYPE_5__ {TYPE_1__ wds; } ;
struct TYPE_6__ {TYPE_2__ ap; } ;

/* Variables and functions */
 int ZM_ERR_WDS_PORT_ID ; 
 size_t ZM_MAX_WDS_SUPPORT ; 
 size_t ZM_NO_WEP ; 
 int ZM_SUCCESS ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfCoreSetKey (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t,int*,scalar_t__*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfiConfigWdsPort(zdev_t* dev, u8_t wdsPortId, u16_t flag, u16_t* wdsAddr,
        u16_t encType, u32_t* wdsKey)
{
    u16_t addr[3];
    u32_t key[4];

    zmw_get_wlan_dev(dev);

    if (wdsPortId >= ZM_MAX_WDS_SUPPORT)
    {
        return ZM_ERR_WDS_PORT_ID;
    }

    if (flag == 1)
    {
        /* Enable WDS port */
        wd->ap.wds.macAddr[wdsPortId][0] = wdsAddr[0];
        wd->ap.wds.macAddr[wdsPortId][1] = wdsAddr[1];
        wd->ap.wds.macAddr[wdsPortId][2] = wdsAddr[2];

        wd->ap.wds.wdsBitmap |= (1 << wdsPortId);
        wd->ap.wds.encryMode[wdsPortId] = (u8_t) encType;

        zfCoreSetKey(dev, 10+ZM_MAX_WDS_SUPPORT, 0, (u8_t) encType, wdsAddr, wdsKey);
    }
    else
    {
        /* Disable WDS port */
        addr[0] = addr[1] = addr[2] = 0;
        key[0] = key[1] = key[2] = key[3] = 0;
        wd->ap.wds.wdsBitmap &= (~(1 << wdsPortId));
        zfCoreSetKey(dev, 10+ZM_MAX_WDS_SUPPORT, 0, ZM_NO_WEP, addr, key);
    }

    return ZM_SUCCESS;
}