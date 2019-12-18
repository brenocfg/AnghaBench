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
struct TYPE_3__ {int currentFrequency; int* bssid; scalar_t__ wepStatus; scalar_t__ encryMode; scalar_t__ keyId; } ;
struct TYPE_4__ {scalar_t__ wlanMode; int frequency; int* macAddr; TYPE_1__ sta; int /*<<< orphan*/  mmseq; } ;

/* Variables and functions */
 int ZM_BIT_15 ; 
 scalar_t__ ZM_ENCRYPTION_WEP_ENABLED ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 scalar_t__ ZM_MODE_PSEUDO ; 
 scalar_t__ ZM_WEP128 ; 
 scalar_t__ ZM_WEP256 ; 
 scalar_t__ ZM_WEP64 ; 
 int ZM_WLAN_FRAME_TYPE_ATIM ; 
 int ZM_WLAN_FRAME_TYPE_BA ; 
 int ZM_WLAN_FRAME_TYPE_PROBEREQ ; 
 int ZM_WLAN_FRAME_TYPE_PSPOLL ; 
 int ZM_WLAN_FRAME_TYPE_QOS_NULL ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfTxGenMmHeader(zdev_t* dev, u8_t frameType, u16_t* dst,
        u16_t* header, u16_t len, zbuf_t* buf, u16_t vap, u8_t encrypt)
{
    //u16_t bodyLen;
    u8_t  hlen = 32;        // MAC ctrl + PHY ctrl + 802.11 MM header

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    /* Generate control setting */
    //bodyLen = zfwBufGetSize(dev, buf);
    header[0] = 24+len+4;   //Length
    if ((dst[0] & 0x1) != 0) //Broadcast, multicast frames
    {
        header[1] = 0xc;            //MAC control, backoff + noack
    }
    else
    {
        header[1] = 0x8;            //MAC control, backoff + (ack)
    }
    /* Dualband Management frame tx Rate */
    if (wd->wlanMode == ZM_MODE_AP)
    {
        if (wd->frequency < 3000)
        {
            /* CCK 1M */
            header[2] = 0x0f00;          //PHY control L
            header[3] = 0x0000;          //PHY control H
        }
        else
        {
            /* CCK 6M */
            header[2] = 0x0f01;          //PHY control L
            header[3] = 0x000B;          //PHY control H
        }
    }
    else
    {
        if (wd->sta.currentFrequency < 3000)
        {
            /* CCK 2M */
            header[2] = 0x0f00;          //PHY control L
            header[3] = 0x0001;          //PHY control H
        }
        else
        {
            /* CCK 6M */
            header[2] = 0x0f01;          //PHY control L
            header[3] = 0x000B;          //PHY control H
        }
    }
    /* Generate WLAN header */
    /* Frame control */
    header[4+0] = frameType;
    /* Duration */
    header[4+1] = 0;

    if (wd->wlanMode == ZM_MODE_INFRASTRUCTURE)
    {
        if ( frameType == ZM_WLAN_FRAME_TYPE_PROBEREQ )
        {
            header[4+8] = 0xFFFF;
            header[4+9] = 0xFFFF;
            header[4+10] = 0xFFFF;
        }
        else if ( frameType == ZM_WLAN_FRAME_TYPE_BA ) {
            /* do nothing */
        }
        else
        {
            header[4+8] = wd->sta.bssid[0];
            header[4+9] = wd->sta.bssid[1];
            header[4+10] = wd->sta.bssid[2];
        }
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

        if ( frameType == ZM_WLAN_FRAME_TYPE_ATIM )
        {
            /* put ATIM to queue 5th */
            //header[2] |= (ZM_BIT_13|ZM_BIT_14);
            header[2] |= ZM_BIT_15;
        }
    }
    else if (wd->wlanMode == ZM_MODE_AP)
    {
        /* Address 3 = BSSID */
        header[4+8] = wd->macAddr[0];
        header[4+9] = wd->macAddr[1];
#ifdef ZM_VAPMODE_MULTILE_SSID
        header[4+10] = wd->macAddr[2]; //Multiple SSID
#else
        header[4+10] = wd->macAddr[2] + (vap<<8); //VAP
#endif
        //if in scan, must set address 3 to broadcast because of some ap would care this
        //if ((wd->heartBeatNotification & ZM_BSSID_LIST_SCAN)
        //        == ZM_BSSID_LIST_SCAN)
        //if FrameType is Probe Request, Address3 should be boradcast
        if (frameType == ZM_WLAN_FRAME_TYPE_PROBEREQ)
        {
            header[4+8] = 0xFFFF;
            header[4+9] = 0xFFFF;
            header[4+10] = 0xFFFF;
        }
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

    if( frameType == ZM_WLAN_FRAME_TYPE_QOS_NULL )
    {
        /*Qos Control*/
        header[4+12] = 0x0;
        hlen+=2;
        header[0]+=2;
    }

    if ( encrypt )
    {
        if ( wd->sta.wepStatus == ZM_ENCRYPTION_WEP_ENABLED )
        {
            if ( (wd->sta.encryMode == ZM_WEP64)||
                 (wd->sta.encryMode == ZM_WEP128)||
                 (wd->sta.encryMode == ZM_WEP256) )
            {
                header[4] |= 0x4000;
                header[16] = 0x0;   //IV
                header[17] = 0x0; //IV
                header[17] |= (((u16_t) wd->sta.keyId) << 14);
                hlen += 4;

                header[0] += 8;         // icvLen = 4;
                header[1] |= 0x40;      // enable encryption on macCtrl
             }
        }
    }

    // Enable HW duration
    if ( frameType != ZM_WLAN_FRAME_TYPE_PSPOLL )
    {
        header[1] |= 0x200;
    }

    return hlen;
}