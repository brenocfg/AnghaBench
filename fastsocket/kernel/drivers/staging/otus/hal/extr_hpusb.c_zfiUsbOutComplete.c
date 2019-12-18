#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_3__ {scalar_t__ EnableHT; } ;
struct TYPE_4__ {scalar_t__ state; scalar_t__ wlanMode; TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 scalar_t__ ZM_MODE_PSEUDO ; 
 scalar_t__ ZM_WLAN_STATE_ENABLED ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfAggTxScheduler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfPushVtxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiUsbOutComplete(zdev_t* dev, zbuf_t *buf, u8_t status, u8_t *hdr) {
#ifndef ZM_ENABLE_AGGREGATION
    if (buf) {
        zfwBufFree(dev, buf, 0);
    }
#else
    #ifdef ZM_BYPASS_AGGR_SCHEDULING
    //Simply free the buf since BA retransmission is done in the firmware
    if (buf)
    {
        zfwBufFree(dev, buf, 0);
    }
    zfPushVtxq(dev);
    #else
    zmw_get_wlan_dev(dev);

    #ifdef ZM_ENABLE_FW_BA_RETRANSMISSION
    //Simply free the buf since BA retransmission is done in the firmware
    if (buf)
    {
        zfwBufFree(dev, buf, 0);
    }
    #else
    u8_t agg;
    u16_t frameType;

    if(!hdr && buf) {
        zfwBufFree(dev, buf, 0);
        //zm_debug_msg0("buf Free due to hdr == NULL");
        return;
    }

    if(hdr && buf) {
        frameType = hdr[8] & 0xf;
        agg = (u8_t)(hdr[2] >> 5 ) & 0x1;
        //zm_debug_msg1("AGG=", agg);

        if (!status) {
            if (agg) {
                //delete buf in ba fail queue??
                //not ganna happen?
            }
            else {
                zfwBufFree(dev, buf, 0);
            }
        }
        else {
            if (agg) {
                //don't do anything
                //zfwBufFree(dev, buf, 0);
            }
            else {
                zfwBufFree(dev, buf, 0);
            }
        }
    }
    #endif

    if (wd->state != ZM_WLAN_STATE_ENABLED) {
        return;
    }

    if( (wd->wlanMode == ZM_MODE_AP) ||
        (wd->wlanMode == ZM_MODE_INFRASTRUCTURE && wd->sta.EnableHT) ||
        (wd->wlanMode == ZM_MODE_PSEUDO) ) {
        zfAggTxScheduler(dev, 0);
    }
    #endif
#endif

    return;

}