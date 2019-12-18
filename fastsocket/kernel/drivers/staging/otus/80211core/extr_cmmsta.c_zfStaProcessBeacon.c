#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsWlanBeaconFrameHeader {int dummy; } ;
struct zsPartnerNotifyEvent {int dummy; } ;
struct zsBssInfo {scalar_t__ macaddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  SignalQuality; int /*<<< orphan*/  SignalStrength1; } ;
struct TYPE_6__ {TYPE_1__ Data; } ;
struct zsAdditionInfo {TYPE_2__ Tail; } ;
struct TYPE_7__ {scalar_t__ oppositeCount; int ssidLen; int* capability; int /*<<< orphan*/  bChannelScan; int /*<<< orphan*/ * ssid; int /*<<< orphan*/  ibssReceiveBeaconCount; int /*<<< orphan*/  rxBeaconCount; scalar_t__ TPCEnable; scalar_t__ DFSEnable; int /*<<< orphan*/  bssid; } ;
struct TYPE_8__ {scalar_t__ wlanMode; TYPE_3__ sta; int /*<<< orphan*/  (* zfcbIbssPartnerNotify ) (int /*<<< orphan*/ *,int,struct zsPartnerNotifyEvent*) ;} ;

/* Variables and functions */
 int ZM_BIT_1 ; 
 int ZM_BIT_4 ; 
 int /*<<< orphan*/  ZM_MAC_WORD_TO_BYTE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  ZM_WLAN_EID_SSID ; 
 int ZM_WLAN_HEADER_A2_OFFSET ; 
 int ZM_WLAN_HEADER_A3_OFFSET ; 
 int capabilityInfo ; 
 int offset ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,struct zsPartnerNotifyEvent*) ; 
 TYPE_4__* wd ; 
 struct zsBssInfo* zfBssInfoAllocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfBssInfoFree (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 int /*<<< orphan*/  zfBssInfoInsertToList (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 int /*<<< orphan*/  zfBssInfoRemoveFromList (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 int /*<<< orphan*/  zfCopyFromRxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int zfFindElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfInitPartnerNotifyEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsPartnerNotifyEvent*) ; 
 int /*<<< orphan*/  zfPowerSavingMgrProcessBeacon (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zfRxBufferEqualToStr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 struct zsBssInfo* zfStaFindBssInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsWlanBeaconFrameHeader*) ; 
 int /*<<< orphan*/  zfStaFindFreeOpposite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int zfStaInitBssInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsWlanBeaconFrameHeader*,struct zsBssInfo*,struct zsAdditionInfo*,int) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaProtErpMonitor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfStaSetOppositeInfoFromRxBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaSignalStatistic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaUpdateDot11HDFS (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaUpdateDot11HTPC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaUpdateWmeParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfUpdateBssid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int zmw_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zmw_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfStaProcessBeacon(zdev_t* dev, zbuf_t* buf, struct zsAdditionInfo* AddInfo) //CWYang(m)
{
    /* Parse TIM and send PS-POLL in power saving mode */
    struct zsWlanBeaconFrameHeader*  pBeaconHeader;
    struct zsBssInfo* pBssInfo;
    u8_t   pBuf[sizeof(struct zsWlanBeaconFrameHeader)];
    u8_t   bssid[6];
    int    res;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    /* sta routine jobs */
    zfStaProtErpMonitor(dev, buf);  /* check protection mode */

    if (zfStaIsConnected(dev))
    {
        ZM_MAC_WORD_TO_BYTE(wd->sta.bssid, bssid);

        if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
        {
            if ( zfRxBufferEqualToStr(dev, buf, bssid, ZM_WLAN_HEADER_A2_OFFSET, 6) )
            {
                zfPowerSavingMgrProcessBeacon(dev, buf);
                zfStaUpdateWmeParameter(dev, buf);
                if (wd->sta.DFSEnable)
                    zfStaUpdateDot11HDFS(dev, buf);
                if (wd->sta.TPCEnable)
                    zfStaUpdateDot11HTPC(dev, buf);
                /* update signal strength and signal quality */
                zfStaSignalStatistic(dev, AddInfo->Tail.Data.SignalStrength1,
                        AddInfo->Tail.Data.SignalQuality); //CWYang(+)
                wd->sta.rxBeaconCount++;
            }
        }
        else if ( wd->wlanMode == ZM_MODE_IBSS )
        {
            if ( zfRxBufferEqualToStr(dev, buf, bssid, ZM_WLAN_HEADER_A3_OFFSET, 6) )
            {
                int res;
                struct zsPartnerNotifyEvent event;

                zm_debug_msg0("20070916 Receive opposite Beacon!");
                zmw_enter_critical_section(dev);
                wd->sta.ibssReceiveBeaconCount++;
                zmw_leave_critical_section(dev);

                res = zfStaSetOppositeInfoFromRxBuf(dev, buf);
                if ( res == 0 )
                {
                    // New peer station found. Notify the wrapper now
                    zfInitPartnerNotifyEvent(dev, buf, &event);
                    if (wd->zfcbIbssPartnerNotify != NULL)
                    {
                        wd->zfcbIbssPartnerNotify(dev, 1, &event);
                    }
                }
                /* update signal strength and signal quality */
                zfStaSignalStatistic(dev, AddInfo->Tail.Data.SignalStrength1,
                        AddInfo->Tail.Data.SignalQuality); //CWYang(+)
            }
            //else if ( wd->sta.ibssPartnerStatus == ZM_IBSS_PARTNER_LOST )
            // Why does this happen in IBSS?? The impact of Vista since
            // we need to tell it the BSSID
#if 0
            else if ( wd->sta.oppositeCount == 0 )
            {   /* IBSS merge if SSID matched */
                if ( (offset = zfFindElement(dev, buf, ZM_WLAN_EID_SSID)) != 0xffff )
                {
                    if ( (wd->sta.ssidLen == zmw_buf_readb(dev, buf, offset+1))&&
                         (zfRxBufferEqualToStr(dev, buf, wd->sta.ssid,
                                               offset+2, wd->sta.ssidLen)) )
                    {
                        capabilityInfo = zmw_buf_readh(dev, buf, 34);

                        if ( capabilityInfo & ZM_BIT_1 )
                        {
                            if ( (wd->sta.capability[0] & ZM_BIT_4) ==
                                 (capabilityInfo & ZM_BIT_4) )
                            {
                                zm_debug_msg0("IBSS merge");
                                zfCopyFromRxBuffer(dev, buf, bssid,
                                                   ZM_WLAN_HEADER_A3_OFFSET, 6);
                                zfUpdateBssid(dev, bssid);
                            }
                        }
                    }
                }
            }
#endif
        }
    }

    /* return if not channel scan */
    if ( !wd->sta.bChannelScan )
    {
        goto zlReturn;
    }

    zfCopyFromRxBuffer(dev, buf, pBuf, 0, sizeof(struct zsWlanBeaconFrameHeader));
    pBeaconHeader = (struct zsWlanBeaconFrameHeader*) pBuf;

    zmw_enter_critical_section(dev);

    //zm_debug_msg1("bss count = ", wd->sta.bssList.bssCount);

    pBssInfo = zfStaFindBssInfo(dev, buf, pBeaconHeader);

    if ( pBssInfo == NULL )
    {
        /* Allocate a new entry if BSS not in the scan list */
        pBssInfo = zfBssInfoAllocate(dev);
        if (pBssInfo != NULL)
        {
            res = zfStaInitBssInfo(dev, buf, pBeaconHeader, pBssInfo, AddInfo, 0);
            //zfDumpSSID(pBssInfo->ssid[1], &(pBssInfo->ssid[2]));
            if ( res != 0 )
            {
                zfBssInfoFree(dev, pBssInfo);
            }
            else
            {
                zfBssInfoInsertToList(dev, pBssInfo);
            }
        }
    }
    else
    {
        res = zfStaInitBssInfo(dev, buf, pBeaconHeader, pBssInfo, AddInfo, 1);
        if (res == 2)
        {
            zfBssInfoRemoveFromList(dev, pBssInfo);
            zfBssInfoFree(dev, pBssInfo);
        }
        else if ( wd->wlanMode == ZM_MODE_IBSS )
        {
            int idx;

            // It would reset the alive counter if the peer station is found!
            zfStaFindFreeOpposite(dev, (u16_t *)pBssInfo->macaddr, &idx);
        }
    }

    zmw_leave_critical_section(dev);

zlReturn:

    return;
}