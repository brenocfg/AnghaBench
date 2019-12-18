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
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_5__ {scalar_t__ wepStatus; int (* pStaRxSecurityCheckCb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ dropUnencryptedPkts; int /*<<< orphan*/ * bssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  swRxDropUnencryptedCount; } ;
struct TYPE_6__ {scalar_t__ wlanMode; TYPE_2__ sta; TYPE_1__ commTally; } ;

/* Variables and functions */
 int ZM_BIT_6 ; 
 scalar_t__ ZM_ENCRYPTION_AES ; 
 scalar_t__ ZM_ENCRYPTION_TKIP ; 
 scalar_t__ ZM_ENCRYPTION_WEP_DISABLED ; 
 int ZM_ERR_DATA_BEFORE_CONNECTED ; 
 int ZM_ERR_DATA_BSSID_NOT_MATCHED ; 
 int ZM_ERR_DATA_NOT_ENCRYPTED ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int ZM_SUCCESS ; 
 int ZM_WLAN_DATA_FRAME ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_DEAUTH ; 
 int ZM_WLAN_HEADER_A1_OFFSET ; 
 scalar_t__ ZM_WLAN_HEADER_A2_OFFSET ; 
 scalar_t__ ZM_WLAN_HEADER_A3_OFFSET ; 
 int /*<<< orphan*/ * sa ; 
 int sa0 ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfRxBufferEqualToStr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,scalar_t__,int) ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int zmw_cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

u16_t zfStaRxValidateFrame(zdev_t* dev, zbuf_t* buf)
{
    u8_t   frameType, frameCtrl;
    u8_t   da0;
    //u16_t  sa[3];
    u16_t  ret;
    u16_t  i;
    //u8_t    sa0;

    zmw_get_wlan_dev(dev);

    frameType = zmw_rx_buf_readb(dev, buf, 0);
    da0 = zmw_rx_buf_readb(dev, buf, ZM_WLAN_HEADER_A1_OFFSET);
    //sa0 = zmw_rx_buf_readb(dev, buf, ZM_WLAN_HEADER_A2_OFFSET);

    if ( (!zfStaIsConnected(dev))&&((frameType & 0xf) == ZM_WLAN_DATA_FRAME) )
    {
        return ZM_ERR_DATA_BEFORE_CONNECTED;
    }


    if ( (zfStaIsConnected(dev))&&((frameType & 0xf) == ZM_WLAN_DATA_FRAME) )
    {
        /* check BSSID */
        if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
        {
            /* Big Endian and Little Endian Compatibility */
            u16_t mac[3];
            mac[0] = zmw_cpu_to_le16(wd->sta.bssid[0]);
            mac[1] = zmw_cpu_to_le16(wd->sta.bssid[1]);
            mac[2] = zmw_cpu_to_le16(wd->sta.bssid[2]);
            if ( !zfRxBufferEqualToStr(dev, buf, (u8_t *)mac,
                                       ZM_WLAN_HEADER_A2_OFFSET, 6) )
            {
/*We will get lots of garbage data, especially in AES mode.*/
/*To avoid sending too many deauthentication frames in STA mode, mark it.*/
#if 0
                /* If unicast frame, send deauth to the transmitter */
                if (( da0 & 0x01 ) == 0)
                {
                    for (i=0; i<3; i++)
                    {
                        sa[i] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET+(i*2));
                    }
					/* If mutilcast address, don't send deauthentication*/
					if (( sa0 & 0x01 ) == 0)
	                  	zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_DEAUTH, sa, 7, 0, 0);
                }
#endif
                return ZM_ERR_DATA_BSSID_NOT_MATCHED;
            }
        }
        else if ( wd->wlanMode == ZM_MODE_IBSS )
        {
            /* Big Endian and Little Endian Compatibility */
            u16_t mac[3];
            mac[0] = zmw_cpu_to_le16(wd->sta.bssid[0]);
            mac[1] = zmw_cpu_to_le16(wd->sta.bssid[1]);
            mac[2] = zmw_cpu_to_le16(wd->sta.bssid[2]);
            if ( !zfRxBufferEqualToStr(dev, buf, (u8_t *)mac,
                                       ZM_WLAN_HEADER_A3_OFFSET, 6) )
            {
                return ZM_ERR_DATA_BSSID_NOT_MATCHED;
            }
        }

        frameCtrl = zmw_rx_buf_readb(dev, buf, 1);

        /* check security bit */
        if ( wd->sta.dropUnencryptedPkts &&
             (wd->sta.wepStatus != ZM_ENCRYPTION_WEP_DISABLED )&&
             ( !(frameCtrl & ZM_BIT_6) ) )
        {   /* security on, but got data without encryption */

            #if 1
            ret = ZM_ERR_DATA_NOT_ENCRYPTED;
            if ( wd->sta.pStaRxSecurityCheckCb != NULL )
            {
                ret = wd->sta.pStaRxSecurityCheckCb(dev, buf);
            }
            else
            {
                ret = ZM_ERR_DATA_NOT_ENCRYPTED;
            }
            if (ret == ZM_ERR_DATA_NOT_ENCRYPTED)
            {
                wd->commTally.swRxDropUnencryptedCount++;
            }
            return ret;
            #else
            if ( (wd->sta.wepStatus != ZM_ENCRYPTION_TKIP)&&
                 (wd->sta.wepStatus != ZM_ENCRYPTION_AES) )
            {
                return ZM_ERR_DATA_NOT_ENCRYPTED;
            }
            #endif
        }
    }

    return ZM_SUCCESS;
}