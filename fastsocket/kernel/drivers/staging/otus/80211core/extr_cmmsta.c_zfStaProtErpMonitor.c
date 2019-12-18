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
struct TYPE_3__ {scalar_t__ bProtectionMode; int /*<<< orphan*/  NonNAPcount; int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int ZM_BIT_1 ; 
 int /*<<< orphan*/  ZM_MAC_WORD_TO_BYTE (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  ZM_WLAN_EID_ERP ; 
 int /*<<< orphan*/  ZM_WLAN_EID_HT_CAPABILITY ; 
 int /*<<< orphan*/  ZM_WLAN_HEADER_A2_OFFSET ; 
 int /*<<< orphan*/  ZM_WLAN_PREN2_EID_HTCAPABILITY ; 
 TYPE_2__* wd ; 
 int zfFindElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpSetSlotTime (int /*<<< orphan*/ *,int) ; 
 scalar_t__ zfRxBufferEqualToStr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfStaProtErpMonitor(zdev_t* dev, zbuf_t* buf)
{
    u16_t   offset;
    u8_t    erp;
    u8_t    bssid[6];

    zmw_get_wlan_dev(dev);

    if ( (wd->wlanMode == ZM_MODE_INFRASTRUCTURE)&&(zfStaIsConnected(dev)) )
    {
        ZM_MAC_WORD_TO_BYTE(wd->sta.bssid, bssid);

        if (zfRxBufferEqualToStr(dev, buf, bssid, ZM_WLAN_HEADER_A2_OFFSET, 6))
        {
            if ( (offset=zfFindElement(dev, buf, ZM_WLAN_EID_ERP)) != 0xffff )
            {
                erp = zmw_rx_buf_readb(dev, buf, offset+2);

                if ( erp & ZM_BIT_1 )
                {
                    //zm_debug_msg0("protection mode on");
                    if (wd->sta.bProtectionMode == FALSE)
                    {
                        wd->sta.bProtectionMode = TRUE;
                        zfHpSetSlotTime(dev, 0);
                    }
                }
                else
                {
                    //zm_debug_msg0("protection mode off");
                    if (wd->sta.bProtectionMode == TRUE)
                    {
                        wd->sta.bProtectionMode = FALSE;
                        zfHpSetSlotTime(dev, 1);
                    }
                }
            }
        }
		//Check the existence of Non-N AP
		//Follow the check the "pBssInfo->EnableHT"
			if ((offset = zfFindElement(dev, buf, ZM_WLAN_EID_HT_CAPABILITY)) != 0xffff)
			{}
			else if ((offset = zfFindElement(dev, buf, ZM_WLAN_PREN2_EID_HTCAPABILITY)) != 0xffff)
			{}
			else
			{wd->sta.NonNAPcount++;}
    }
}