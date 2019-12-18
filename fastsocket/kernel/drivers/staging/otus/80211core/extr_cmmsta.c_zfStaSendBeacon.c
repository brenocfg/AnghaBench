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
typedef  int u16_t ;
struct TYPE_5__ {int* bssid; scalar_t__ authMode; scalar_t__ ibssAdditionalIESize; int /*<<< orphan*/ * capability; } ;
struct TYPE_4__ {scalar_t__ bIbssGMode; } ;
struct TYPE_6__ {int* macAddr; int beaconInterval; scalar_t__ frequency; int supportMode; scalar_t__ wlanMode; TYPE_2__ sta; TYPE_1__ wfc; scalar_t__ erpElement; int /*<<< orphan*/  mmseq; } ;

/* Variables and functions */
 scalar_t__ ZM_AUTH_MODE_WPA2PSK ; 
 scalar_t__ ZM_CH_G_14 ; 
 scalar_t__ ZM_MODE_IBSS ; 
 int /*<<< orphan*/  ZM_RATE_SET_CCK ; 
 int /*<<< orphan*/  ZM_RATE_SET_OFDM ; 
 int ZM_WIRELESS_MODE_24_54 ; 
 int ZM_WIRELESS_MODE_24_N ; 
 int /*<<< orphan*/  ZM_WLAN_EID_EXTENDED_RATE ; 
 int /*<<< orphan*/  ZM_WLAN_EID_SUPPORT_RATE ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_AUTH ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfHpSendBeacon (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfMmAddExtendedHTCapability (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfMmAddHTCapability (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfMmAddIeDs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfMmAddIeErp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfMmAddIeSupportRate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfStaAddIbssAdditionalIE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfStaAddIeIbss (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfStaAddIeSsid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zfwBufAllocate (int /*<<< orphan*/ *,int) ; 
 int zfwStaAddIeWpaRsn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void zfStaSendBeacon(zdev_t* dev)
{
    zbuf_t* buf;
    u16_t offset, seq;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    //zm_debug_msg0("\n");

    /* TBD : Maximum size of beacon */
    if ((buf = zfwBufAllocate(dev, 1024)) == NULL)
    {
        zm_debug_msg0("Allocate beacon buffer failed");
        return;
    }

    offset = 0;
    /* wlan header */
    /* Frame control */
    zmw_tx_buf_writeh(dev, buf, offset, 0x0080);
    offset+=2;
    /* Duration */
    zmw_tx_buf_writeh(dev, buf, offset, 0x0000);
    offset+=2;
    /* Address 1 */
    zmw_tx_buf_writeh(dev, buf, offset, 0xffff);
    offset+=2;
    zmw_tx_buf_writeh(dev, buf, offset, 0xffff);
    offset+=2;
    zmw_tx_buf_writeh(dev, buf, offset, 0xffff);
    offset+=2;
    /* Address 2 */
    zmw_tx_buf_writeh(dev, buf, offset, wd->macAddr[0]);
    offset+=2;
    zmw_tx_buf_writeh(dev, buf, offset, wd->macAddr[1]);
    offset+=2;
    zmw_tx_buf_writeh(dev, buf, offset, wd->macAddr[2]);
    offset+=2;
    /* Address 3 */
    zmw_tx_buf_writeh(dev, buf, offset, wd->sta.bssid[0]);
    offset+=2;
    zmw_tx_buf_writeh(dev, buf, offset, wd->sta.bssid[1]);
    offset+=2;
    zmw_tx_buf_writeh(dev, buf, offset, wd->sta.bssid[2]);
    offset+=2;

    /* Sequence number */
    zmw_enter_critical_section(dev);
    seq = ((wd->mmseq++)<<4);
    zmw_leave_critical_section(dev);
    zmw_tx_buf_writeh(dev, buf, offset, seq);
    offset+=2;

    /* 24-31 Time Stamp : hardware will fill this field */
    offset+=8;

    /* Beacon Interval */
    zmw_tx_buf_writeh(dev, buf, offset, wd->beaconInterval);
    offset+=2;

    /* Capability */
    zmw_tx_buf_writeb(dev, buf, offset++, wd->sta.capability[0]);
    zmw_tx_buf_writeb(dev, buf, offset++, wd->sta.capability[1]);

    /* SSID */
    offset = zfStaAddIeSsid(dev, buf, offset);

    if(wd->frequency <= ZM_CH_G_14)  // 2.4 GHz  b+g
    {

    	/* Support Rate */
    	offset = zfMmAddIeSupportRate(dev, buf, offset,
                                  		ZM_WLAN_EID_SUPPORT_RATE, ZM_RATE_SET_CCK);

    	/* DS parameter set */
    	offset = zfMmAddIeDs(dev, buf, offset);

    	offset = zfStaAddIeIbss(dev, buf, offset);

        if( wd->wfc.bIbssGMode
            && (wd->supportMode & (ZM_WIRELESS_MODE_24_54|ZM_WIRELESS_MODE_24_N)) )    // Only accompany with enabling a mode .
        {
      	    /* ERP Information */
       	    wd->erpElement = 0;
       	    offset = zfMmAddIeErp(dev, buf, offset);
       	}

       	/* TODO : country information */
        /* RSN */
        if ( wd->sta.authMode == ZM_AUTH_MODE_WPA2PSK )
        {
            offset = zfwStaAddIeWpaRsn(dev, buf, offset, ZM_WLAN_FRAME_TYPE_AUTH);
        }

        if( wd->wfc.bIbssGMode
            && (wd->supportMode & (ZM_WIRELESS_MODE_24_54|ZM_WIRELESS_MODE_24_N)) )    // Only accompany with enabling a mode .
        {
            /* Enable G Mode */
            /* Extended Supported Rates */
       	    offset = zfMmAddIeSupportRate(dev, buf, offset,
                                   		    ZM_WLAN_EID_EXTENDED_RATE, ZM_RATE_SET_OFDM);
	    }
    }
    else    // 5GHz a
    {
        /* Support Rate a Mode */
    	offset = zfMmAddIeSupportRate(dev, buf, offset,
        	                            ZM_WLAN_EID_SUPPORT_RATE, ZM_RATE_SET_OFDM);

        /* DS parameter set */
    	offset = zfMmAddIeDs(dev, buf, offset);

    	offset = zfStaAddIeIbss(dev, buf, offset);

        /* TODO : country information */
        /* RSN */
        if ( wd->sta.authMode == ZM_AUTH_MODE_WPA2PSK )
        {
            offset = zfwStaAddIeWpaRsn(dev, buf, offset, ZM_WLAN_FRAME_TYPE_AUTH);
        }
    }

    if ( wd->wlanMode != ZM_MODE_IBSS )
    {
        /* TODO : Need to check if it is ok */
        /* HT Capabilities Info */
        offset = zfMmAddHTCapability(dev, buf, offset);

        /* Extended HT Capabilities Info */
        offset = zfMmAddExtendedHTCapability(dev, buf, offset);
    }

    if ( wd->sta.ibssAdditionalIESize )
        offset = zfStaAddIbssAdditionalIE(dev, buf, offset);

    /* 1212 : write to beacon fifo */
    /* 1221 : write to share memory */
    zfHpSendBeacon(dev, buf, offset);

    /* Free beacon buffer */
    //zfwBufFree(dev, buf, 0);
}