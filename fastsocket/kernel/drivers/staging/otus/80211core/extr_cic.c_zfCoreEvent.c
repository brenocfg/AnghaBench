#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  size_t u8_t ;
typedef  int u32_t ;
typedef  size_t u16_t ;
typedef  int /*<<< orphan*/  s8_t ;
typedef  int /*<<< orphan*/  rsp ;
struct TYPE_7__ {scalar_t__ powerSaveMode; size_t staPSDataCount; int ibssAtimTimer; int atimWindow; TYPE_1__* oppositeInfo; int /*<<< orphan*/ ** staPSDataQueue; } ;
struct TYPE_9__ {size_t* bcmcTail; size_t* bcmcHead; TYPE_3__* staTable; int /*<<< orphan*/ *** bcmcArray; } ;
struct TYPE_10__ {scalar_t__ wlanMode; scalar_t__ CurrentDtimCount; TYPE_2__ sta; TYPE_4__ ap; } ;
struct TYPE_8__ {int /*<<< orphan*/  rcCell; } ;
struct TYPE_6__ {int /*<<< orphan*/  rcCell; } ;

/* Variables and functions */
 int ZM_BCMC_ARRAY_SIZE ; 
 int ZM_BIT_15 ; 
 int /*<<< orphan*/  ZM_EXTERNAL_ALLOC_BUF ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_STA_PS_NONE ; 
 TYPE_5__* wd ; 
 size_t zfApFindSta (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  zfApSendBeacon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfApSendFailure (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ zfPhyCtrlToRate (int) ; 
 int /*<<< orphan*/  zfPowerSavingMgrPreTBTTInterrupt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfRateCtrlTxFailEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  zfRateCtrlTxSuccessEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zfStaFindOppositeByMACAddr (int /*<<< orphan*/ *,size_t*,size_t*) ; 
 int /*<<< orphan*/  zfStaSendBeacon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTxSendEth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfCoreEvent(zdev_t* dev, u16_t event, u8_t* rsp)
{
    u16_t i;
    zbuf_t* psBuf;
    u8_t moreData;
    u8_t vap = 0;
    u8_t peerIdx;
    s8_t res;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();


    if (event == 0) //Beacon Event
    {
        if ( wd->wlanMode == ZM_MODE_AP )
        {
            zfApSendBeacon(dev);

            if (wd->CurrentDtimCount == 0)
            {
                /* TODO : Send queued broadcast frames at BC/MC event */
                do
                {
                    psBuf = NULL;
                    moreData = 0;
                    zmw_enter_critical_section(dev);
                    if (wd->ap.bcmcTail[vap] != wd->ap.bcmcHead[vap])
                    {
                        //zm_msg0_mm(ZM_LV_0, "Send BCMC frames");
                        psBuf = wd->ap.bcmcArray[vap][wd->ap.bcmcHead[vap]];
                        wd->ap.bcmcHead[vap] = (wd->ap.bcmcHead[vap] + 1)
                                & (ZM_BCMC_ARRAY_SIZE - 1);
                        if (wd->ap.bcmcTail[vap] != wd->ap.bcmcHead[vap])
                        {
                            moreData = 0x20;
                        }
                    }
                    zmw_leave_critical_section(dev);
                    if (psBuf != NULL)
                    {
                        /* TODO : config moreData bit */
                        zfTxSendEth(dev, psBuf, 0, ZM_EXTERNAL_ALLOC_BUF,
                                moreData);
                    }
                } while(psBuf != NULL);

            }
        }
        else
        {
            /* STA mode */
            if ( wd->sta.powerSaveMode > ZM_STA_PS_NONE )
            {
                /* send queued packets */
                for(i=0; i<wd->sta.staPSDataCount; i++)
                {
                    zfTxSendEth(dev, wd->sta.staPSDataQueue[i], 0,
                                ZM_EXTERNAL_ALLOC_BUF, 0);
                }

                wd->sta.staPSDataCount = 0;
            }

            if ( wd->wlanMode == ZM_MODE_IBSS )
            {
                zfStaSendBeacon(dev);
                wd->sta.ibssAtimTimer = ZM_BIT_15 | wd->sta.atimWindow;
            }

            zfPowerSavingMgrPreTBTTInterrupt(dev);
        }
    } //if (event == 0) //Beacon Event
    else if (event == 1) //Retry completed event
    {
        u32_t retryRate;

        retryRate = (u32_t)(rsp[6]) + (((u32_t)(rsp[7]))<<8)
                + (((u32_t)(rsp[8]))<<16) + (((u32_t)(rsp[9]))<<24);
        /* Degrade Tx Rate */
        if (wd->wlanMode == ZM_MODE_AP)
        {
            zmw_enter_critical_section(dev);
            if ((i=zfApFindSta(dev, (u16_t*)rsp)) != 0xffff)
            {
                zfRateCtrlTxFailEvent(dev, &wd->ap.staTable[i].rcCell, 0,(u32_t)zfPhyCtrlToRate(retryRate));
            }
            zmw_leave_critical_section(dev);
        }
        else
        {
            zmw_enter_critical_section(dev);
            res = zfStaFindOppositeByMACAddr(dev, (u16_t*)rsp, &peerIdx);
            if ( res == 0 )
            {
                zfRateCtrlTxFailEvent(dev, &wd->sta.oppositeInfo[peerIdx].rcCell, 0,(u32_t)zfPhyCtrlToRate(retryRate));
            }
            zmw_leave_critical_section(dev);
        }
    } //else if (event == 1) //Retry completed event
    else if (event == 2) //Tx Fail event
    {
        u32_t retryRate;

        retryRate = (u32_t)(rsp[6]) + (((u32_t)(rsp[7]))<<8)
                + (((u32_t)(rsp[8]))<<16) + (((u32_t)(rsp[9]))<<24);

        /* Degrade Tx Rate */
        if (wd->wlanMode == ZM_MODE_AP)
        {
            zmw_enter_critical_section(dev);
            if ((i=zfApFindSta(dev, (u16_t*)rsp)) != 0xffff)
            {
                zfRateCtrlTxFailEvent(dev, &wd->ap.staTable[i].rcCell, 0,(u32_t)zfPhyCtrlToRate(retryRate));
            }
            zmw_leave_critical_section(dev);

            zfApSendFailure(dev, rsp);
        }
        else
        {
            zmw_enter_critical_section(dev);
            res = zfStaFindOppositeByMACAddr(dev, (u16_t*)rsp, &peerIdx);
            if ( res == 0 )
            {
                zfRateCtrlTxFailEvent(dev, &wd->sta.oppositeInfo[peerIdx].rcCell, 0,(u32_t)zfPhyCtrlToRate(retryRate));
            }
            zmw_leave_critical_section(dev);
        }
    } //else if (event == 2) //Tx Fail event
    else if (event == 3) //Tx Comp event
    {
        u32_t retryRate;

        retryRate = (u32_t)(rsp[6]) + (((u32_t)(rsp[7]))<<8)
                + (((u32_t)(rsp[8]))<<16) + (((u32_t)(rsp[9]))<<24);

        /* TODO : Tx completed, used for rate control probing */
        if (wd->wlanMode == ZM_MODE_AP)
        {
            zmw_enter_critical_section(dev);
            if ((i=zfApFindSta(dev, (u16_t*)rsp)) != 0xffff)
            {
                zfRateCtrlTxSuccessEvent(dev, &wd->ap.staTable[i].rcCell, zfPhyCtrlToRate(retryRate));
            }
            zmw_leave_critical_section(dev);
        }
        else
        {
            zmw_enter_critical_section(dev);
            res = zfStaFindOppositeByMACAddr(dev, (u16_t*)rsp, &peerIdx);
            if ( res == 0 )
            {
                zfRateCtrlTxSuccessEvent(dev, &wd->sta.oppositeInfo[peerIdx].rcCell, zfPhyCtrlToRate(retryRate));
            }
            zmw_leave_critical_section(dev);
        }
    } //else if (event == 3) //Tx Comp event
    else if (event == 4) //BA failed count
    {
        u32_t fail;
        u32_t rate;
        peerIdx = 0;

        fail=((u32_t*)rsp)[0] & 0xFFFF;
        rate=((u32_t*)rsp)[0] >> 16;

        if (rate > 15) {
            rate = (rate & 0xF) + 12 + 2;
        }
        else {
            rate = rate + 12;
        }

        zmw_enter_critical_section(dev);
        zfRateCtrlTxFailEvent(dev, &wd->sta.oppositeInfo[peerIdx].rcCell, (u8_t)rate, fail);
        zmw_leave_critical_section(dev);
    }
}