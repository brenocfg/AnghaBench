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
struct TYPE_3__ {int apBitmap; scalar_t__* hideSsid; int* ssidLen; scalar_t__** ssid; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_3 ; 
 int ZM_MAX_AP_SUPPORT ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 int /*<<< orphan*/  ZM_WLAN_EID_SSID ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_PROBERSP ; 
 TYPE_2__* wd ; 
 int zfFindElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 scalar_t__ zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfStaProcessProbeReq(zdev_t* dev, zbuf_t* buf, u16_t* src)
{
    u16_t offset;
    u8_t len;
    u16_t i, j;
    u16_t sendFlag;

    zmw_get_wlan_dev(dev);

    /* check mode : AP/IBSS */
    if ((wd->wlanMode != ZM_MODE_AP) || (wd->wlanMode != ZM_MODE_IBSS))
    {
        zm_msg0_mm(ZM_LV_3, "Ignore probe req");
        return;
    }

    /* check SSID */
    if ((offset = zfFindElement(dev, buf, ZM_WLAN_EID_SSID)) == 0xffff)
    {
        zm_msg0_mm(ZM_LV_3, "probe req SSID not found");
        return;
    }

    len = zmw_rx_buf_readb(dev, buf, offset+1);

    for (i=0; i<ZM_MAX_AP_SUPPORT; i++)
    {
        if ((wd->ap.apBitmap & (i<<i)) != 0)
        {
            sendFlag = 0;
            /* boardcast SSID */
            if ((len == 0) && (wd->ap.hideSsid[i] == 0))
            {
                sendFlag = 1;
            }
            /* Not broadcast SSID */
            else if (wd->ap.ssidLen[i] == len)
            {
                for (j=0; j<len; j++)
                {
                    if (zmw_rx_buf_readb(dev, buf, offset+1+j)
                            != wd->ap.ssid[i][j])
                    {
                        break;
                    }
                }
                if (j == len)
                {
                    sendFlag = 1;
                }
            }
            if (sendFlag == 1)
            {
                /* Send probe response */
                zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_PROBERSP, src, i, 0, 0);
            }
        }
    }
}