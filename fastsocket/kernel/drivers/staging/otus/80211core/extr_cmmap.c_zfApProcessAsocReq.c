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
struct TYPE_3__ {int vapNumber; int* ssidLen; int** ssid; scalar_t__* wlanType; scalar_t__ uapsdEnabled; int* wpaSupport; int* stawpaLen; int /*<<< orphan*/ * stawpaIe; } ;
struct TYPE_4__ {TYPE_1__ ap; int /*<<< orphan*/  (* zfcbCencAsocNotify ) (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* zfcbAsocNotify ) (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 int ZM_MAX_WPAIE_SIZE ; 
 int /*<<< orphan*/  ZM_STATE_ASOC ; 
 int /*<<< orphan*/  ZM_WLAN_EID_CENC_IE ; 
 int /*<<< orphan*/  ZM_WLAN_EID_EXTENDED_RATE ; 
 int /*<<< orphan*/  ZM_WLAN_EID_HT_CAPABILITY ; 
 int /*<<< orphan*/  ZM_WLAN_EID_RSN_IE ; 
 int /*<<< orphan*/  ZM_WLAN_EID_SSID ; 
 int /*<<< orphan*/  ZM_WLAN_EID_WPA_IE ; 
 int ZM_WLAN_FRAME_TYPE_ASOCREQ ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_ASOCRSP ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_DEAUTH ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_REASOCRSP ; 
 scalar_t__ ZM_WLAN_TYPE_PURE_B ; 
 scalar_t__ ZM_WLAN_TYPE_PURE_G ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* wd ; 
 int zfApAddSta (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  zfApStoreAsocReqIe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfCopyFromRxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int zfFindElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfFindWifiElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int,int) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zm_msg1_mm (int /*<<< orphan*/ ,char*,int) ; 
 int zmw_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfApProcessAsocReq(zdev_t* dev, zbuf_t* buf, u16_t* src, u16_t apId)
{
    u16_t aid = 0xffff;
    u8_t frameType;
    u16_t offset;
    u8_t staType = 0;
    u8_t qosType = 0;
    u8_t qosInfo = 0;
    u8_t tmp;
    u16_t i, j, k;
    u16_t encMode = 0;

    zmw_get_wlan_dev(dev);
    /* AP : check SSID */
    if ((offset = zfFindElement(dev, buf, ZM_WLAN_EID_SSID)) != 0xffff)
    {
        k = 0;
        for (j = 0; j < wd->ap.vapNumber; j++)
        {
            if ((tmp = zmw_buf_readb(dev, buf, offset+1))
                        != wd->ap.ssidLen[j])
            {
                k++;
            }
        }
        if (k == wd->ap.vapNumber)
        {
            goto zlDeauth;
        }

        k = 0;
        for (j = 0; j < wd->ap.vapNumber; j++)
        {
            for (i=0; i<wd->ap.ssidLen[j]; i++)
            {
                if ((tmp = zmw_buf_readb(dev, buf, offset+2+i))
                        != wd->ap.ssid[j][i])
                {
                    break;
                }
            }
            if (i == wd->ap.ssidLen[j])
            {
                apId = j;
            }
            else
            {
                k++;
            }
        }
        if (k == wd->ap.vapNumber)
        {
            goto zlDeauth;
        }
    }

    /* TODO : check capability */

    /* AP : check support rate */
    if ((offset = zfFindElement(dev, buf, ZM_WLAN_EID_EXTENDED_RATE)) != 0xffff)
    {
        /* 11g STA */
        staType = 1;
    }
    //CWYang(+)
    if ((offset = zfFindElement(dev, buf, ZM_WLAN_EID_HT_CAPABILITY)) != 0xffff)
    {
        /* 11n STA */
        staType = 2;
    }

    /* TODO : do not allow 11b STA to associated in Pure G mode */
    if (wd->ap.wlanType[apId] == ZM_WLAN_TYPE_PURE_G && staType == 0)
    {
        zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_DEAUTH, src, 3, 0, 0);
        return;
    }

    /* In pure B mode, we set G STA into B mode */
    if (wd->ap.wlanType[apId] == ZM_WLAN_TYPE_PURE_B && staType == 1)
    {
        staType = 0;
    }

    /* AP : check 11i and WPA */
    /* AP : check 11h */

    /* AP : check WME */
    if ((offset = zfFindWifiElement(dev, buf, 2, 0)) != 0xffff)
    {
        /* WME STA */
        qosType = 1;
        zm_msg0_mm(ZM_LV_0, "WME STA");

        if (wd->ap.uapsdEnabled != 0)
        {
            qosInfo = zmw_rx_buf_readb(dev, buf, offset+8);
        }
    }

    if (wd->ap.wpaSupport[apId] == 1)
    {
        if ( (offset = zfFindElement(dev, buf, ZM_WLAN_EID_WPA_IE)) != 0xffff )
        {
            /* get WPA IE */
            u8_t length = zmw_rx_buf_readb(dev, buf, offset+1);
            if (length+2 < ZM_MAX_WPAIE_SIZE)
            {
                zfCopyFromRxBuffer(dev, buf, wd->ap.stawpaIe[apId], offset, length+2);
                wd->ap.stawpaLen[apId] = length+2;
                encMode = 1;


                zm_msg1_mm(ZM_LV_0, "WPA Mode zfwAsocNotify, apId=", apId);

                /* AP : Call zfwAsocNotify() */
                if (wd->zfcbAsocNotify != NULL)
                {
                    wd->zfcbAsocNotify(dev, src, wd->ap.stawpaIe[apId], wd->ap.stawpaLen[apId], apId);
                }
            }
            else
            {
                goto zlDeauth;
            }
        }
        else if ( (offset = zfFindElement(dev, buf, ZM_WLAN_EID_RSN_IE)) != 0xffff )
        {
            /* get RSN IE */
            u8_t length = zmw_rx_buf_readb(dev, buf, offset+1);
            if (length+2 < ZM_MAX_WPAIE_SIZE)
            {
                zfCopyFromRxBuffer(dev, buf, wd->ap.stawpaIe[apId], offset, length+2);
                wd->ap.stawpaLen[apId] = length+2;
                encMode = 1;

                zm_msg1_mm(ZM_LV_0, "RSN Mode zfwAsocNotify, apId=", apId);

                /* AP : Call zfwAsocNotify() */
                if (wd->zfcbAsocNotify != NULL)
                {
                    wd->zfcbAsocNotify(dev, src, wd->ap.stawpaIe[apId], wd->ap.stawpaLen[apId], apId);
                }
            }
            else
            {
                goto zlDeauth;
            }
        }
#ifdef ZM_ENABLE_CENC
        else if ( (offset = zfFindElement(dev, buf, ZM_WLAN_EID_CENC_IE)) != 0xffff )
        {
            /* get CENC IE */
            u8_t length = zmw_rx_buf_readb(dev, buf, offset+1);

            if (length+2 < ZM_MAX_WPAIE_SIZE)
            {
                zfCopyFromRxBuffer(dev, buf, wd->ap.stawpaIe[apId], offset, length+2);
                wd->ap.stawpaLen[apId] = length+2;
                encMode = 1;

                zm_msg1_mm(ZM_LV_0, "CENC Mode zfwAsocNotify, apId=", apId);

                /* AP : Call zfwAsocNotify() */
                if (wd->zfcbCencAsocNotify != NULL)
                {
                    wd->zfcbCencAsocNotify(dev, src, wd->ap.stawpaIe[apId],
                            wd->ap.stawpaLen[apId], apId);
                }
            }
            else
            {
                goto zlDeauth;
            }
        }
#endif //ZM_ENABLE_CENC
        else
        {   /* ap is encryption but sta has no wpa/rsn ie */
            zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_DEAUTH, src, 6, 0, 0);
            return;
        }
    }
    /* sta has wpa/rsn ie but ap is no encryption */
    if ((wd->ap.wpaSupport[apId] == 0) && (encMode == 1))
    {
        zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_DEAUTH, src, 6, 0, 0);
        return;
    }

    /* AP : update STA to asoc */
    aid = zfApAddSta(dev, src, ZM_STATE_ASOC, apId, staType, qosType, qosInfo);

    zfApStoreAsocReqIe(dev, buf, aid);

zlDeauth:
    /* AP : send asoc rsp2 */
    if (aid != 0xffff)
    {
        frameType = zmw_rx_buf_readb(dev, buf, 0);

        if (frameType == ZM_WLAN_FRAME_TYPE_ASOCREQ)
        {
            zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_ASOCRSP, src, 0, aid+1, apId);
        }
        else
        {
            zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_REASOCRSP, src, 0, aid+1, apId);
        }
    }
    else
    {
        /* TODO : send deauthentication */
        zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_DEAUTH, src, 6, 0, 0);
    }

    return;
}