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
typedef  int /*<<< orphan*/  zbuf_t ;
struct zsAdditionInfo {int dummy; } ;
struct TYPE_4__ {scalar_t__ bssCount; } ;
struct TYPE_5__ {TYPE_1__ bssList; } ;
struct TYPE_6__ {int heartBeatNotification; TYPE_2__ sta; } ;

/* Variables and functions */
 int ZM_BSSID_LIST_SCAN ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 scalar_t__ ZM_MAX_BSS ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfProcessProbeRsp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsAdditionInfo*) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfApProcessProbeRsp(zdev_t* dev, zbuf_t* buf, struct zsAdditionInfo* AddInfo)
{
#if 0
    zmw_get_wlan_dev(dev);

    zm_msg0_mm(ZM_LV_0, "Rx probersp");

    /* Gather scan result */

    //zm_debug_msg1("bssList Count = ", wd->sta.bssList.bssCount);
    /* return if not in scanning */
    if ((wd->heartBeatNotification & ZM_BSSID_LIST_SCAN)
            != ZM_BSSID_LIST_SCAN)
    {
        return;
    }

    //if ( wd->sta.pUpdateBssList->bssCount == ZM_MAX_BSS )
    if ( wd->sta.bssList.bssCount == ZM_MAX_BSS )
    {
        return;
    }

    zfProcessProbeRsp(dev, buf, AddInfo);

#endif
}