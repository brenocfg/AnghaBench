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
 int ZM_WLAN_EID_VENDOR_PRIVATE ; 
 scalar_t__ zfRxBufferEqualToStr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* zgElementOffsetTable ; 
 int /*<<< orphan*/  zm_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfFindXRElement(zdev_t* dev, zbuf_t* buf, u8_t type)
{
    u8_t subType;
    u16_t offset;
    u16_t bufLen;
    u16_t elen;
    u8_t id;
    u8_t ouixr[6] = {0x00,0x03,0x7f,0x03, 0x01, 0x00};

    zmw_get_wlan_dev(dev);

    /* Get offset of first element */
    subType = (zmw_rx_buf_readb(dev, buf, 0) >> 4);
    if ((offset = zgElementOffsetTable[subType]) == 0xff)
    {
        zm_assert(0);
    }

    /* Plus wlan header */
    offset += 24;

    bufLen = zfwBufGetSize(dev, buf);
    /* Search loop */
    while ((offset+2)<bufLen)                   // including element ID and length (2bytes)
    {
        /* Search target element */
        if ((id = zmw_rx_buf_readb(dev, buf, offset)) == ZM_WLAN_EID_VENDOR_PRIVATE)
        {
            /* Bingo */
            if ((elen = zmw_rx_buf_readb(dev, buf, offset+1))>(bufLen - offset))
            {
                /* Element length error */
                return 0xffff;
            }

            if ( elen == 0 )
            {
                return 0xffff;
            }

            if (zfRxBufferEqualToStr(dev, buf, ouixr, offset+2, 6) && ( zmw_rx_buf_readb(dev, buf, offset+1) >= 6))
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