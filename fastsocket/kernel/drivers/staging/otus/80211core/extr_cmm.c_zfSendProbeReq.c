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
typedef  int u8_t ;
typedef  scalar_t__ u16_t ;
struct TYPE_9__ {scalar_t__ bIbssGMode; } ;
struct TYPE_8__ {int currentFrequency; } ;
struct TYPE_7__ {TYPE_1__* probingSsidList; } ;
struct TYPE_10__ {int supportMode; scalar_t__ wlanMode; TYPE_4__ wfc; TYPE_3__ sta; TYPE_2__ ws; } ;
struct TYPE_6__ {scalar_t__ ssidLen; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_IBSS ; 
 int /*<<< orphan*/  ZM_RATE_SET_CCK ; 
 int /*<<< orphan*/  ZM_RATE_SET_OFDM ; 
 int ZM_WIRELESS_MODE_24_54 ; 
 int ZM_WIRELESS_MODE_24_N ; 
 int /*<<< orphan*/  ZM_WLAN_EID_EXTENDED_RATE ; 
 scalar_t__ ZM_WLAN_EID_SSID ; 
 int /*<<< orphan*/  ZM_WLAN_EID_SUPPORT_RATE ; 
 TYPE_5__* wd ; 
 int /*<<< orphan*/  zfCopyToIntTxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ zfMmAddIeSupportRate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

u16_t zfSendProbeReq(zdev_t* dev, zbuf_t* buf, u16_t offset, u8_t bWithSSID)
{
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();


    /* SSID */
    if (bWithSSID == 0)  /* broadcast ssid */
    {
        //zmw_leave_critical_section(dev);
        zmw_tx_buf_writeb(dev, buf, offset++, ZM_WLAN_EID_SSID);
        zmw_tx_buf_writeb(dev, buf, offset++, 0);   /* length = 0 */
    }
    else
    {
        zmw_enter_critical_section(dev);
        if (wd->ws.probingSsidList[bWithSSID-1].ssidLen == 0)
        {
            zmw_tx_buf_writeb(dev, buf, offset++, ZM_WLAN_EID_SSID);
            zmw_tx_buf_writeb(dev, buf, offset++, 0);   /* length = 0 */
        }
        else
        {
            zmw_tx_buf_writeb(dev, buf, offset++, ZM_WLAN_EID_SSID);
            zmw_tx_buf_writeb(dev, buf, offset++,
                    wd->ws.probingSsidList[bWithSSID-1].ssidLen);
            zfCopyToIntTxBuffer(dev, buf,
                    wd->ws.probingSsidList[bWithSSID-1].ssid,
                    offset,
                    wd->ws.probingSsidList[bWithSSID-1].ssidLen); /* ssid */
            offset += wd->ws.probingSsidList[bWithSSID-1].ssidLen;
        }
        zmw_leave_critical_section(dev);
    }

    /* Supported rates */
    if ( wd->sta.currentFrequency < 3000 )
    {   /* 802.11b+g */
        offset = zfMmAddIeSupportRate(dev, buf, offset,
                                      ZM_WLAN_EID_SUPPORT_RATE, ZM_RATE_SET_CCK);

        if (wd->supportMode & (ZM_WIRELESS_MODE_24_54|ZM_WIRELESS_MODE_24_N)) {
            if (wd->wlanMode == ZM_MODE_IBSS) {
                if (wd->wfc.bIbssGMode) {
                    offset = zfMmAddIeSupportRate(dev, buf, offset,
                                      ZM_WLAN_EID_EXTENDED_RATE, ZM_RATE_SET_OFDM);
                }
            } else {
                offset = zfMmAddIeSupportRate(dev, buf, offset,
                                      ZM_WLAN_EID_EXTENDED_RATE, ZM_RATE_SET_OFDM);
            }
        }
    }
    else
    {  /* 802.11a */
        offset = zfMmAddIeSupportRate(dev, buf, offset,
                                      ZM_WLAN_EID_SUPPORT_RATE, ZM_RATE_SET_OFDM);
    }

    return offset;
}