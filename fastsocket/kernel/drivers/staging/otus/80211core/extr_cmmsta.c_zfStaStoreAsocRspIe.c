#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  size_t u32_t ;
typedef  int u16_t ;
struct TYPE_7__ {int ChannelInfo; } ;
struct TYPE_6__ {int HtCapInfo; } ;
struct TYPE_8__ {TYPE_2__ HtInfo; TYPE_1__ HtCap; } ;
struct TYPE_9__ {size_t asocRspFrameBodySize; int currentFrequency; int EnableHT; TYPE_3__ ie; void** asocRspFrameBody; } ;
struct TYPE_10__ {int supportMode; int BandWidth40; int ExtOffset; TYPE_4__ sta; } ;

/* Variables and functions */
 int ExtHtCap_ExtChannelOffsetBelow ; 
 int HTCAP_SupChannelWidthSet ; 
 int /*<<< orphan*/  ZM_LV_1 ; 
 int ZM_WIRELESS_MODE_24_N ; 
 int ZM_WIRELESS_MODE_5_N ; 
 int /*<<< orphan*/  ZM_WLAN_EID_EXTENDED_HT_CAPABILITY ; 
 int /*<<< orphan*/  ZM_WLAN_EID_HT_CAPABILITY ; 
 int /*<<< orphan*/  ZM_WLAN_PREN2_EID_HTCAPABILITY ; 
 int /*<<< orphan*/  ZM_WLAN_PREN2_EID_HTINFORMATION ; 
 TYPE_5__* wd ; 
 int zfFindElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_msg2_mm (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 void* zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfStaStoreAsocRspIe(zdev_t* dev, zbuf_t* buf)
{
    u16_t offset;
    u32_t i;
    u16_t length;
    u8_t  *htcap;
    u8_t  asocBw40 = 0;
    u8_t  asocExtOffset = 0;

    zmw_get_wlan_dev(dev);

    for (i=0; i<wd->sta.asocRspFrameBodySize; i++)
    {
        wd->sta.asocRspFrameBody[i] = zmw_rx_buf_readb(dev, buf, i+24);
    }

    /* HT capabilities: 28 octets */
    if (    ((wd->sta.currentFrequency > 3000) && !(wd->supportMode & ZM_WIRELESS_MODE_5_N))
         || ((wd->sta.currentFrequency < 3000) && !(wd->supportMode & ZM_WIRELESS_MODE_24_N)) )
    {
        /* not 11n AP */
        htcap = (u8_t *)&wd->sta.ie.HtCap;
        for (i=0; i<28; i++)
        {
            htcap[i] = 0;
        }
        wd->BandWidth40 = 0;
        wd->ExtOffset = 0;
        return;
    }

    if ((offset = zfFindElement(dev, buf, ZM_WLAN_EID_HT_CAPABILITY)) != 0xffff)
    {
        /* atheros pre n */
        zm_debug_msg0("atheros pre n");
        htcap = (u8_t *)&wd->sta.ie.HtCap;
        htcap[0] = zmw_rx_buf_readb(dev, buf, offset);
        htcap[1] = 26;
        for (i=1; i<=26; i++)
        {
            htcap[i+1] = zmw_rx_buf_readb(dev, buf, offset + i);
            zm_msg2_mm(ZM_LV_1, "ASOC:  HT Capabilities, htcap=", htcap[i+1]);
        }
    }
    else if ((offset = zfFindElement(dev, buf, ZM_WLAN_PREN2_EID_HTCAPABILITY)) != 0xffff)
    {
        /* pre n 2.0 standard */
        zm_debug_msg0("pre n 2.0 standard");
        htcap = (u8_t *)&wd->sta.ie.HtCap;
        for (i=0; i<28; i++)
        {
            htcap[i] = zmw_rx_buf_readb(dev, buf, offset + i);
            zm_msg2_mm(ZM_LV_1, "ASOC:  HT Capabilities, htcap=", htcap[i]);
        }
    }
    else
    {
        /* not 11n AP */
        htcap = (u8_t *)&wd->sta.ie.HtCap;
        for (i=0; i<28; i++)
        {
            htcap[i] = 0;
        }
        wd->BandWidth40 = 0;
        wd->ExtOffset = 0;
        return;
    }

    asocBw40 = (u8_t)((wd->sta.ie.HtCap.HtCapInfo & HTCAP_SupChannelWidthSet) >> 1);

    /* HT information */
    if ((offset = zfFindElement(dev, buf, ZM_WLAN_EID_EXTENDED_HT_CAPABILITY)) != 0xffff)
    {
        /* atheros pre n */
        zm_debug_msg0("atheros pre n HTINFO");
        length = 22;
        htcap = (u8_t *)&wd->sta.ie.HtInfo;
        htcap[0] = zmw_rx_buf_readb(dev, buf, offset);
        htcap[1] = 22;
        for (i=1; i<=22; i++)
        {
            htcap[i+1] = zmw_rx_buf_readb(dev, buf, offset + i);
            zm_msg2_mm(ZM_LV_1, "ASOC:  HT Info, htinfo=", htcap[i+1]);
        }
    }
    else if ((offset = zfFindElement(dev, buf, ZM_WLAN_PREN2_EID_HTINFORMATION)) != 0xffff)
    {
        /* pre n 2.0 standard */
        zm_debug_msg0("pre n 2.0 standard HTINFO");
        length = zmw_rx_buf_readb(dev, buf, offset + 1);
        htcap = (u8_t *)&wd->sta.ie.HtInfo;
        for (i=0; i<24; i++)
        {
            htcap[i] = zmw_rx_buf_readb(dev, buf, offset + i);
            zm_msg2_mm(ZM_LV_1, "ASOC:  HT Info, htinfo=", htcap[i]);
        }
    }
    else
    {
        zm_debug_msg0("no HTINFO");
        htcap = (u8_t *)&wd->sta.ie.HtInfo;
        for (i=0; i<24; i++)
        {
            htcap[i] = 0;
        }
    }
    asocExtOffset = wd->sta.ie.HtInfo.ChannelInfo & ExtHtCap_ExtChannelOffsetBelow;

    if ((wd->sta.EnableHT == 1) && (asocBw40 == 1) && ((asocExtOffset == 1) || (asocExtOffset == 3)))
    {
        wd->BandWidth40 = asocBw40;
        wd->ExtOffset = asocExtOffset;
    }
    else
    {
        wd->BandWidth40 = 0;
        wd->ExtOffset = 0;
    }

    return;
}