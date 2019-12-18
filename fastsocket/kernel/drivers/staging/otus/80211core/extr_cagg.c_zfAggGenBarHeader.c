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
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_2__ {int* macAddr; scalar_t__ wlanMode; int /*<<< orphan*/  mmseq; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 int ZM_WLAN_FRAME_TYPE_BAR ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfAggGenBarHeader(zdev_t* dev, u16_t* dst,
        u16_t* header, u16_t len, zbuf_t* buf, u16_t vap, u8_t encrypt)
{
    u8_t  hlen = 16+8;        // MAC ctrl + PHY ctrl + 802.11 MM header
    //u8_t frameType = ZM_WLAN_FRAME_TYPE_ACTION;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    /*
     * Generate control setting
     */
    //bodyLen = zfwBufGetSize(dev, buf);
    header[0] = 16+len+4;   //Length
    header[1] = 0x8;        //MAC control, backoff + (ack)

#if 1
    /* CCK 1M */
    header[2] = 0x0f00;          //PHY control L
    header[3] = 0x0000;          //PHY control H
#else
    /* CCK 6M */
    header[2] = 0x0f01;          //PHY control L
    header[3] = 0x000B;          //PHY control H

#endif
    /*
     * Generate WLAN header
     * Frame control frame type and subtype
     */
    header[4+0] = ZM_WLAN_FRAME_TYPE_BAR;
    /*
     * Duration
     */
    header[4+1] = 0;

    /* Address 1 = DA */
    header[4+2] = dst[0];
    header[4+3] = dst[1];
    header[4+4] = dst[2];

    /* Address 2 = SA */
    header[4+5] = wd->macAddr[0];
    header[4+6] = wd->macAddr[1];
    if (wd->wlanMode == ZM_MODE_AP)
    {
#ifdef ZM_VAPMODE_MULTILE_SSID
        header[4+7] = wd->macAddr[2]; //Multiple SSID
#else
        header[4+7] = wd->macAddr[2] + (vap<<8); //VAP
#endif
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