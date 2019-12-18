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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int u16_t ;
struct zsAdditionInfo {int dummy; } ;
struct TYPE_11__ {size_t CurChIndex; TYPE_4__* allowChannel; } ;
struct TYPE_9__ {int /*<<< orphan*/  DFSEnable; } ;
struct TYPE_8__ {TYPE_1__* staTable; } ;
struct TYPE_12__ {scalar_t__ wlanMode; TYPE_5__ regulationTable; TYPE_3__ sta; TYPE_2__ ap; } ;
struct TYPE_10__ {int channelFlags; } ;
struct TYPE_7__ {int vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_2 ; 
 scalar_t__ ZM_MODE_AP ; 
 int ZM_REG_FLAG_CHANNEL_CSA ; 
 int ZM_REG_FLAG_CHANNEL_PASSIVE ; 
#define  ZM_WLAN_FRAME_TYPE_ACTION 139 
#define  ZM_WLAN_FRAME_TYPE_ASOCREQ 138 
#define  ZM_WLAN_FRAME_TYPE_ASOCRSP 137 
#define  ZM_WLAN_FRAME_TYPE_ATIM 136 
#define  ZM_WLAN_FRAME_TYPE_AUTH 135 
#define  ZM_WLAN_FRAME_TYPE_BEACON 134 
#define  ZM_WLAN_FRAME_TYPE_DEAUTH 133 
#define  ZM_WLAN_FRAME_TYPE_DISASOC 132 
#define  ZM_WLAN_FRAME_TYPE_PROBEREQ 131 
#define  ZM_WLAN_FRAME_TYPE_PROBERSP 130 
#define  ZM_WLAN_FRAME_TYPE_REASOCREQ 129 
#define  ZM_WLAN_FRAME_TYPE_REASOCRSP 128 
 TYPE_6__* wd ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfApProcessAction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfApProcessAsocReq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  zfApProcessAuth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  zfApProcessBeacon (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfApProcessDeauth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  zfApProcessDisasoc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  zfApProcessProbeRsp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsAdditionInfo*) ; 
 int /*<<< orphan*/  zfProcessProbeReq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfStaProcessAction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaProcessAsocReq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaProcessAsocRsp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaProcessAtim (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaProcessAuth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaProcessBeacon (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsAdditionInfo*) ; 
 int /*<<< orphan*/  zfStaProcessDeauth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaProcessDisasoc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaProcessProbeRsp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsAdditionInfo*) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zm_msg2_mm (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfProcessManagement(zdev_t* dev, zbuf_t* buf, struct zsAdditionInfo* AddInfo) //CWYang(m)
{
    u8_t frameType;
    u16_t ta[3];
    u16_t ra[3];
    u16_t vap = 0, index = 0;
    //u16_t i;

    zmw_get_wlan_dev(dev);

    ra[0] = zmw_rx_buf_readh(dev, buf, 4);
    ra[1] = zmw_rx_buf_readh(dev, buf, 6);
    ra[2] = zmw_rx_buf_readh(dev, buf, 8);

    ta[0] = zmw_rx_buf_readh(dev, buf, 10);
    ta[1] = zmw_rx_buf_readh(dev, buf, 12);
    ta[2] = zmw_rx_buf_readh(dev, buf, 14);

    frameType = zmw_rx_buf_readb(dev, buf, 0);

    if (wd->wlanMode == ZM_MODE_AP)
    {
#if 1
        vap = 0;
        if ((ra[0] & 0x1) != 1)
        {
            /* AP : Find virtual AP */
            if ((index = zfApFindSta(dev, ta)) != 0xffff)
            {
                vap = wd->ap.staTable[index].vap;
            }
        }
        zm_msg2_mm(ZM_LV_2, "vap=", vap);
#endif

        /* Dispatch by frame type */
        switch (frameType)
        {
                /* Beacon */
            case ZM_WLAN_FRAME_TYPE_BEACON :
                zfApProcessBeacon(dev, buf);
                break;
                /* Authentication */
            case ZM_WLAN_FRAME_TYPE_AUTH :
                zfApProcessAuth(dev, buf, ta, vap);
                break;
                /* Association request */
            case ZM_WLAN_FRAME_TYPE_ASOCREQ :
                /* Reassociation request */
            case ZM_WLAN_FRAME_TYPE_REASOCREQ :
                zfApProcessAsocReq(dev, buf, ta, vap);
                break;
                /* Association response */
            case ZM_WLAN_FRAME_TYPE_ASOCRSP :
                //zfApProcessAsocRsp(dev, buf);
                break;
                /* Deauthentication */
            case ZM_WLAN_FRAME_TYPE_DEAUTH :
                zfApProcessDeauth(dev, buf, ta, vap);
                break;
                /* Disassociation */
            case ZM_WLAN_FRAME_TYPE_DISASOC :
                zfApProcessDisasoc(dev, buf, ta, vap);
                break;
                /* Probe request */
            case ZM_WLAN_FRAME_TYPE_PROBEREQ :
                zfProcessProbeReq(dev, buf, ta);
                break;
                /* Probe response */
            case ZM_WLAN_FRAME_TYPE_PROBERSP :
                zfApProcessProbeRsp(dev, buf, AddInfo);
                break;
                /* Action */
            case ZM_WLAN_FRAME_TYPE_ACTION :
                zfApProcessAction(dev, buf);
                break;
        }
    }
    else //if ((wd->wlanMode == ZM_MODE_INFRASTRUCTURE) || (wd->wlanMode == ZM_MODE_IBSS))
    {
        /* Dispatch by frame type */
        switch (frameType)
        {
                /* Beacon */
            case ZM_WLAN_FRAME_TYPE_BEACON :
                /* if enable 802.11h and current chanel is silent but receive beacon from other AP */
                if (((wd->regulationTable.allowChannel[wd->regulationTable.CurChIndex].channelFlags
                        & ZM_REG_FLAG_CHANNEL_CSA) != 0) && wd->sta.DFSEnable)
                {
                    wd->regulationTable.allowChannel[wd->regulationTable.CurChIndex].channelFlags
                            &= ~(ZM_REG_FLAG_CHANNEL_CSA & ZM_REG_FLAG_CHANNEL_PASSIVE);
                }
                zfStaProcessBeacon(dev, buf, AddInfo); //CWYang(m)
                break;
                /* Authentication */
            case ZM_WLAN_FRAME_TYPE_AUTH :
                /* TODO : vap parameter is useless in STA mode, get rid of it */
                zfStaProcessAuth(dev, buf, ta, 0);
                break;
                /* Association request */
            case ZM_WLAN_FRAME_TYPE_ASOCREQ :
                /* TODO : vap parameter is useless in STA mode, get rid of it */
                zfStaProcessAsocReq(dev, buf, ta, 0);
                break;
                /* Association response */
            case ZM_WLAN_FRAME_TYPE_ASOCRSP :
                /* Reassociation request */
            case ZM_WLAN_FRAME_TYPE_REASOCRSP :
                zfStaProcessAsocRsp(dev, buf);
                break;
                /* Deauthentication */
            case ZM_WLAN_FRAME_TYPE_DEAUTH :
                zm_debug_msg0("Deauthentication received");
                zfStaProcessDeauth(dev, buf);
                break;
                /* Disassociation */
            case ZM_WLAN_FRAME_TYPE_DISASOC :
                zm_debug_msg0("Disassociation received");
                zfStaProcessDisasoc(dev, buf);
                break;
                /* Probe request */
            case ZM_WLAN_FRAME_TYPE_PROBEREQ :
                zfProcessProbeReq(dev, buf, ta);
                break;
                /* Probe response */
            case ZM_WLAN_FRAME_TYPE_PROBERSP :
                /* if enable 802.11h and current chanel is silent but receive probe response from other AP */
                if (((wd->regulationTable.allowChannel[wd->regulationTable.CurChIndex].channelFlags
                        & ZM_REG_FLAG_CHANNEL_CSA) != 0) && wd->sta.DFSEnable)
                {
                    wd->regulationTable.allowChannel[wd->regulationTable.CurChIndex].channelFlags
                            &= ~(ZM_REG_FLAG_CHANNEL_CSA & ZM_REG_FLAG_CHANNEL_PASSIVE);
                }
                zfStaProcessProbeRsp(dev, buf, AddInfo);
                break;

            case ZM_WLAN_FRAME_TYPE_ATIM:
                zfStaProcessAtim(dev, buf);
                break;
                /* Action */
            case ZM_WLAN_FRAME_TYPE_ACTION :
                zm_msg0_mm(ZM_LV_2, "ProcessActionMgtFrame");
                zfStaProcessAction(dev, buf);
                break;
        }
    }
}