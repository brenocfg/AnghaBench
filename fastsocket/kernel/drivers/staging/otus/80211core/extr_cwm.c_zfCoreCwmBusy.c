#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u16_t ;
struct TYPE_11__ {scalar_t__ cw_mode; void* cw_width; } ;
struct TYPE_8__ {int ChannelInfo; } ;
struct TYPE_7__ {int HtCapInfo; } ;
struct TYPE_9__ {TYPE_2__ HtInfo; TYPE_1__ HtCap; } ;
struct TYPE_10__ {TYPE_3__ ie; } ;
struct TYPE_12__ {scalar_t__ wlanMode; TYPE_5__ cwm; TYPE_4__ sta; } ;

/* Variables and functions */
 scalar_t__ CWM_MODE20 ; 
 scalar_t__ CWM_MODE40 ; 
 void* CWM_WIDTH20 ; 
 void* CWM_WIDTH40 ; 
 int ExtHtCap_ExtChannelOffsetAbove ; 
 int ExtHtCap_RecomTxWidthSet ; 
 int HTCAP_SupChannelWidthSet ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 scalar_t__ ZM_MODE_PSEUDO ; 
 TYPE_6__* wd ; 
 int /*<<< orphan*/  zm_msg1_mm (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfCoreCwmBusy(zdev_t* dev, u16_t busy)
{

    zmw_get_wlan_dev(dev);

    zm_msg1_mm(ZM_LV_0, "CwmBusy=", busy);

    if(wd->cwm.cw_mode == CWM_MODE20) {
        wd->cwm.cw_width = CWM_WIDTH20;
        return;
    }

    if(wd->cwm.cw_mode == CWM_MODE40) {
        wd->cwm.cw_width = CWM_WIDTH40;
        return;
    }

    if (busy) {
        wd->cwm.cw_width = CWM_WIDTH20;
        return;
    }


    if((wd->wlanMode == ZM_MODE_INFRASTRUCTURE || wd->wlanMode == ZM_MODE_PSEUDO ||
        wd->wlanMode == ZM_MODE_IBSS)) {
        if ((wd->sta.ie.HtCap.HtCapInfo & HTCAP_SupChannelWidthSet) &&
            (wd->sta.ie.HtInfo.ChannelInfo & ExtHtCap_RecomTxWidthSet) &&
            (wd->sta.ie.HtInfo.ChannelInfo & ExtHtCap_ExtChannelOffsetAbove)) {

            wd->cwm.cw_width = CWM_WIDTH40;
        }
        else {
            wd->cwm.cw_width = CWM_WIDTH20;
        }

        return;
    }

    if(wd->wlanMode == ZM_MODE_AP) {
        wd->cwm.cw_width = CWM_WIDTH40;
    }

}