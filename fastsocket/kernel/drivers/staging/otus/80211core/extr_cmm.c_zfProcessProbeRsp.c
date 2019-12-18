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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsWlanProbeRspFrameHeader {int dummy; } ;
struct zsBssInfo {scalar_t__ macaddr; } ;
struct zsAdditionInfo {int dummy; } ;
struct TYPE_2__ {scalar_t__ wlanMode; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_IBSS ; 
 TYPE_1__* wd ; 
 struct zsBssInfo* zfBssInfoAllocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfBssInfoFree (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 int /*<<< orphan*/  zfBssInfoInsertToList (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 int /*<<< orphan*/  zfBssInfoRemoveFromList (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 int /*<<< orphan*/  zfCopyFromRxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct zsBssInfo* zfStaFindBssInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsWlanProbeRspFrameHeader*) ; 
 int /*<<< orphan*/  zfStaFindFreeOpposite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int zfStaInitBssInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsWlanProbeRspFrameHeader*,struct zsBssInfo*,struct zsAdditionInfo*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfProcessProbeRsp(zdev_t* dev, zbuf_t* buf, struct zsAdditionInfo* AddInfo)
{
    /* Gather scan result */
    /* Parse TIM and send PS-POLL in power saving mode */
    struct zsWlanProbeRspFrameHeader*  pProbeRspHeader;
    struct zsBssInfo* pBssInfo;
    u8_t   pBuf[sizeof(struct zsWlanProbeRspFrameHeader)];
    int    res;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zfCopyFromRxBuffer(dev, buf, pBuf, 0,
                       sizeof(struct zsWlanProbeRspFrameHeader));
    pProbeRspHeader = (struct zsWlanProbeRspFrameHeader*) pBuf;

    zmw_enter_critical_section(dev);

    //zm_debug_msg1("bss count = ", wd->sta.bssList.bssCount);

    pBssInfo = zfStaFindBssInfo(dev, buf, pProbeRspHeader);

    //if ( i == wd->sta.bssList.bssCount )
    if ( pBssInfo == NULL )
    {
        /* Allocate a new entry if BSS not in the scan list */
        pBssInfo = zfBssInfoAllocate(dev);
        if (pBssInfo != NULL)
        {
            res = zfStaInitBssInfo(dev, buf, pProbeRspHeader, pBssInfo, AddInfo, 0);
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
        res = zfStaInitBssInfo(dev, buf, pProbeRspHeader, pBssInfo, AddInfo, 1);
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

    return;
}