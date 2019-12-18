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
typedef  size_t u8_t ;
typedef  scalar_t__ u16_t ;
typedef  int /*<<< orphan*/  s8_t ;
struct TYPE_5__ {scalar_t__* bssid; TYPE_1__* oppositeInfo; } ;
struct TYPE_6__ {scalar_t__ wlanMode; TYPE_2__ sta; } ;
struct TYPE_4__ {scalar_t__ aliveCounter; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_DISCONNECT_AUTH_FAILED ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_DISCONNECT_DEAUTH ; 
 scalar_t__ ZM_WLAN_HEADER_A2_OFFSET ; 
 scalar_t__ ZM_WLAN_HEADER_A3_OFFSET ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfStaConnectFail (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  zfStaFindOppositeByMACAddr (int /*<<< orphan*/ *,scalar_t__*,size_t*) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnecting (int /*<<< orphan*/ *) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 scalar_t__ zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

void zfStaProcessDeauth(zdev_t* dev, zbuf_t* buf)
{
    u16_t apMacAddr[3];

    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    /* STA : if SA=connected AP then disconnect with AP */
    if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
    {
        apMacAddr[0] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A3_OFFSET);
        apMacAddr[1] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A3_OFFSET+2);
        apMacAddr[2] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A3_OFFSET+4);
  	if ((apMacAddr[0] == wd->sta.bssid[0]) && (apMacAddr[1] == wd->sta.bssid[1]) && (apMacAddr[2] == wd->sta.bssid[2]))
        {
            if (zfwBufGetSize(dev, buf) >= 24+2) //not a malformed frame
            {
                if ( zfStaIsConnected(dev) )
                {
                    zfStaConnectFail(dev, ZM_STATUS_MEDIA_DISCONNECT_DEAUTH, wd->sta.bssid, 2);
                }
                else if (zfStaIsConnecting(dev))
                {
                    zfStaConnectFail(dev, ZM_STATUS_MEDIA_DISCONNECT_AUTH_FAILED, wd->sta.bssid, 3);
                }
                else
                {
                }
            }
        }
    }
    else if ( wd->wlanMode == ZM_MODE_IBSS )
    {
        u16_t peerMacAddr[3];
        u8_t  peerIdx;
        s8_t  res;

        if ( zfStaIsConnected(dev) )
        {
            peerMacAddr[0] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET);
            peerMacAddr[1] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET+2);
            peerMacAddr[2] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET+4);

            zmw_enter_critical_section(dev);
            res = zfStaFindOppositeByMACAddr(dev, peerMacAddr, &peerIdx);
            if ( res == 0 )
            {
                wd->sta.oppositeInfo[peerIdx].aliveCounter = 0;
            }
            zmw_leave_critical_section(dev);
        }
    }
}