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
struct TYPE_3__ {int* bssid; } ;
struct TYPE_4__ {scalar_t__ wlanMode; int* macAddr; int /*<<< orphan*/  mmseq; TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 scalar_t__ ZM_MODE_PSEUDO ; 
 int ZM_WLAN_FRAME_TYPE_ACTION ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfAggGenAddbaHeader(zdev_t* dev, u16_t* dst,
        u16_t* header, u16_t len, zbuf_t* buf, u16_t vap, u8_t encrypt)
{
    u8_t  hlen = 32;        // MAC ctrl + PHY ctrl + 802.11 MM header
    //u8_t frameType = ZM_WLAN_FRAME_TYPE_ACTION;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    /*
     * Generate control setting
     */
    //bodyLen = zfwBufGetSize(dev, buf);
    header[0] = 24+len+4;   //Length
    header[1] = 0x8;        //MAC control, backoff + (ack)

#if 0
    /* CCK 1M */
    header[2] = 0x0f00;          //PHY control L
    header[3] = 0x0000;          //PHY control H
#else
    /* OFDM 6M */
    header[2] = 0x0f01;          //PHY control L
    header[3] = 0x000B;          //PHY control H
#endif

    /*
     * Generate WLAN header
     * Frame control frame type and subtype
     */
    header[4+0] = ZM_WLAN_FRAME_TYPE_ACTION;
    /*
     * Duration
     */
    header[4+1] = 0;

    if (wd->wlanMode == ZM_MODE_INFRASTRUCTURE)
    {
        header[4+8] = wd->sta.bssid[0];
        header[4+9] = wd->sta.bssid[1];
        header[4+10] = wd->sta.bssid[2];
    }
    else if (wd->wlanMode == ZM_MODE_PSEUDO)
    {
        /* Address 3 = 00:00:00:00:00:00 */
        header[4+8] = 0;
        header[4+9] = 0;
        header[4+10] = 0;
    }
    else if (wd->wlanMode == ZM_MODE_IBSS)
    {
        header[4+8] = wd->sta.bssid[0];
        header[4+9] = wd->sta.bssid[1];
        header[4+10] = wd->sta.bssid[2];
    }
    else if (wd->wlanMode == ZM_MODE_AP)
    {
        /* Address 3 = BSSID */
        header[4+8] = wd->macAddr[0];
        header[4+9] = wd->macAddr[1];
        header[4+10] = wd->macAddr[2] + (vap<<8);
    }

    /* Address 1 = DA */
    header[4+2] = dst[0];
    header[4+3] = dst[1];
    header[4+4] = dst[2];

    /* Address 2 = SA */
    header[4+5] = wd->macAddr[0];
    header[4+6] = wd->macAddr[1];
    if (wd->wlanMode == ZM_MODE_AP)
    {
        header[4+7] = wd->macAddr[2] + (vap<<8);
    }
    else
    {
        header[4+7] = wd->macAddr[2];
    }

    /* Sequence Control */
    zmw_enter_critical_section(dev);
    header[4+11] = ((wd->mmseq++)<<4);
    zmw_leave_critical_section(dev);


    return hlen;
}