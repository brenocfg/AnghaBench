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
typedef  int u16_t ;
struct TYPE_3__ {scalar_t__ beaconCounter; scalar_t__ vapNumber; int* capab; scalar_t__* hideSsid; scalar_t__* wlanType; int* wpaSupport; int qosMode; } ;
struct TYPE_4__ {int* macAddr; int beaconInterval; int frequency; TYPE_1__ ap; int /*<<< orphan*/  mmseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_LV_2 ; 
 int /*<<< orphan*/  ZM_RATE_SET_CCK ; 
 int /*<<< orphan*/  ZM_RATE_SET_OFDM ; 
 int /*<<< orphan*/  ZM_WLAN_EID_EXTENDED_RATE ; 
 int /*<<< orphan*/  ZM_WLAN_EID_SSID ; 
 int /*<<< orphan*/  ZM_WLAN_EID_SUPPORT_RATE ; 
 scalar_t__ ZM_WLAN_TYPE_PURE_B ; 
 TYPE_2__* wd ; 
 int zfApAddIeSsid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int zfApAddIeTim (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int zfApAddIeWmePara (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfHpSendBeacon (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfMmAddExtendedHTCapability (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfMmAddHTCapability (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfMmAddIeDs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfMmAddIeErp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfMmAddIeSupportRate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfMmAddIeWpa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * zfwBufAllocate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zm_msg1_mm (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void zfApSendBeacon(zdev_t* dev)
{
    zbuf_t* buf;
    u16_t offset;
    u16_t vap;
    u16_t seq;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    wd->ap.beaconCounter++;
    if (wd->ap.beaconCounter >= wd->ap.vapNumber)
    {
        wd->ap.beaconCounter = 0;
    }
    vap = wd->ap.beaconCounter;


    zm_msg1_mm(ZM_LV_2, "Send beacon, vap=", vap);

    /* TBD : Maximum size of beacon */
    if ((buf = zfwBufAllocate(dev, 1024)) == NULL)
    {
        zm_msg0_mm(ZM_LV_0, "Alloc beacon buf Fail!");
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
#ifdef ZM_VAPMODE_MULTILE_SSID
    zmw_tx_buf_writeh(dev, buf, offset, wd->macAddr[2]); //Multiple SSID
#else
    zmw_tx_buf_writeh(dev, buf, offset, (wd->macAddr[2]+(vap<<8))); //VAP
#endif
    offset+=2;
    /* Address 3 */
    zmw_tx_buf_writeh(dev, buf, offset, wd->macAddr[0]);
    offset+=2;
    zmw_tx_buf_writeh(dev, buf, offset, wd->macAddr[1]);
    offset+=2;
#ifdef ZM_VAPMODE_MULTILE_SSID
    zmw_tx_buf_writeh(dev, buf, offset, wd->macAddr[2]); //Multiple SSID
#else
    zmw_tx_buf_writeh(dev, buf, offset, (wd->macAddr[2]+(vap<<8))); //VAP
#endif
    offset+=2;

    /* Sequence number */
    zmw_enter_critical_section(dev);
    seq = ((wd->mmseq++)<<4);
    zmw_leave_critical_section(dev);
    zmw_tx_buf_writeh(dev, buf, offset, seq);
    offset+=2;

    /* 24-31 Time Stamp : hardware will fill this field */
    zmw_tx_buf_writeh(dev, buf, offset, 0);
    zmw_tx_buf_writeh(dev, buf, offset+2, 0);
    zmw_tx_buf_writeh(dev, buf, offset+4, 0);
    zmw_tx_buf_writeh(dev, buf, offset+6, 0);
    offset+=8;

    /* Beacon Interval */
    zmw_tx_buf_writeh(dev, buf, offset, wd->beaconInterval);
    offset+=2;

    /* Capability */
    zmw_tx_buf_writeh(dev, buf, offset, wd->ap.capab[vap]);
    offset+=2;

    /* SSID */
    if (wd->ap.hideSsid[vap] == 0)
    {
        offset = zfApAddIeSsid(dev, buf, offset, vap);
    }
    else
    {
        zmw_tx_buf_writeb(dev, buf, offset++, ZM_WLAN_EID_SSID);
        zmw_tx_buf_writeb(dev, buf, offset++, 0);

    }

    /* Support Rate */
    if ( wd->frequency < 3000 )
    {
    offset = zfMmAddIeSupportRate(dev, buf, offset,
                                  ZM_WLAN_EID_SUPPORT_RATE, ZM_RATE_SET_CCK);
    }
    else
    {
        offset = zfMmAddIeSupportRate(dev, buf, offset,
                                  ZM_WLAN_EID_SUPPORT_RATE, ZM_RATE_SET_OFDM);
    }

    /* DS parameter set */
    offset = zfMmAddIeDs(dev, buf, offset);

    /* TIM */
    offset = zfApAddIeTim(dev, buf, offset, vap);

    /* If WLAN Type is not PURE B */
    if (wd->ap.wlanType[vap] != ZM_WLAN_TYPE_PURE_B)
    {
        if ( wd->frequency < 3000 )
        {
        /* ERP Information */
        offset = zfMmAddIeErp(dev, buf, offset);

        /* Extended Supported Rates */
        offset = zfMmAddIeSupportRate(dev, buf, offset,
                                      ZM_WLAN_EID_EXTENDED_RATE, ZM_RATE_SET_OFDM);
    }
    }

    /* TODO : country information */
    /* TODO : RSN */
    if (wd->ap.wpaSupport[vap] == 1)
    {
        offset = zfMmAddIeWpa(dev, buf, offset, vap);
    }

    /* WME Parameters */
    if (wd->ap.qosMode == 1)
    {
        offset = zfApAddIeWmePara(dev, buf, offset, vap);
    }

    /* HT Capabilities Info */
    offset = zfMmAddHTCapability(dev, buf, offset);

    /* Extended HT Capabilities Info */
    offset = zfMmAddExtendedHTCapability(dev, buf, offset);

    /* 1212 : write to beacon fifo */
    /* 1221 : write to share memory */
    zfHpSendBeacon(dev, buf, offset);

    /* Free beacon buffer */
    /* TODO: In order to fit the madwifi beacon architecture, we need to
       free beacon buffer in the HAL layer.
     */

    //zfwBufFree(dev, buf, 0);
}