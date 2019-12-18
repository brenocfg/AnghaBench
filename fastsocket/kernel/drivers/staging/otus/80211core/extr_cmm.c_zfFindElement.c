#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int u16_t ;

/* Variables and functions */
 int ZM_WLAN_EID_EXTENDED_HT_CAPABILITY ; 
 int ZM_WLAN_EID_HT_CAPABILITY ; 
 int ZM_WLAN_EID_SSID ; 
 int ZM_WLAN_EID_WPA_IE ; 
 scalar_t__ zfRxBufferEqualToStr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* zgElementOffsetTable ; 
 int /*<<< orphan*/  zm_assert (int /*<<< orphan*/ ) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfFindElement(zdev_t* dev, zbuf_t* buf, u8_t eid)
{
    u8_t subType;
    u16_t offset;
    u16_t bufLen;
    u16_t elen;
    u8_t id, HTEid=0;
    u8_t oui[4] = {0x00, 0x50, 0xf2, 0x01};
    u8_t oui11n[3] = {0x00,0x90,0x4C};
    u8_t HTType = 0;

    /* Get offset of first element */
    subType = (zmw_rx_buf_readb(dev, buf, 0) >> 4);
    if ((offset = zgElementOffsetTable[subType]) == 0xff)
    {
        zm_assert(0);
    }

    /* Plus wlan header */
    offset += 24;

    // jhlee HT 0

    if ((eid == ZM_WLAN_EID_HT_CAPABILITY) ||
        (eid == ZM_WLAN_EID_EXTENDED_HT_CAPABILITY))
    {
        HTEid = eid;
        eid = ZM_WLAN_EID_WPA_IE;
        HTType = 1;
    }


    bufLen = zfwBufGetSize(dev, buf);
    /* Search loop */
    while ((offset+2)<bufLen)                   // including element ID and length (2bytes)
    {
        /* Search target element */
        if ((id = zmw_rx_buf_readb(dev, buf, offset)) == eid)
        {
            /* Bingo */
            if ((elen = zmw_rx_buf_readb(dev, buf, offset+1))>(bufLen - offset))
            {
                /* Element length error */
                return 0xffff;
            }

            if ( elen == 0 && eid != ZM_WLAN_EID_SSID)
            {
                /* Element length error */
                return 0xffff;
            }

            if ( eid == ZM_WLAN_EID_WPA_IE )
            {
                /* avoid sta to be thought use 11n when find a WPA_IE */
                if ( (HTType == 0) && zfRxBufferEqualToStr(dev, buf, oui, offset+2, 4) )
                {
                    return offset;
                }

                // jhlee HT 0
                // CWYang(+)

                if ((HTType == 1) && ( zfRxBufferEqualToStr(dev, buf, oui11n, offset+2, 3) ))
                {
                    if ( zmw_rx_buf_readb(dev, buf, offset+5) == HTEid )
                    {
                        return offset + 5;
                    }
                }

            }
            else
            {
                return offset;
            }
        }
        /* Advance to next element */
        #if 1
        elen = zmw_rx_buf_readb(dev, buf, offset+1);
        #else
        if ((elen = zmw_rx_buf_readb(dev, buf, offset+1)) == 0)
        {
            return 0xffff;
        }
        #endif

        offset += (elen+2);
    }
    return 0xffff;
}