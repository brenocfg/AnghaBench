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
typedef  size_t u8_t ;
typedef  int u16_t ;

/* Variables and functions */
 size_t ZM_WLAN_EID_WIFI_IE ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* zgElementOffsetTable ; 
 int /*<<< orphan*/  zm_assert (int /*<<< orphan*/ ) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfFindMarvelExtCap(zdev_t* dev, zbuf_t* buf)
{
    u8_t subType;
    u16_t offset;
    u16_t bufLen;
    u16_t elen;
    u8_t id;
    u8_t tmp;

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
        if ((id = zmw_rx_buf_readb(dev, buf, offset)) == ZM_WLAN_EID_WIFI_IE)
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

            if (((tmp = zmw_rx_buf_readb(dev, buf, offset+2)) == 0x00)
                  && ((tmp = zmw_rx_buf_readb(dev, buf, offset+3)) == 0x50)
                  && ((tmp = zmw_rx_buf_readb(dev, buf, offset+4)) == 0x43))

            {
                return offset;
            }
        }

        /* Advance to next element */
        if ((elen = zmw_rx_buf_readb(dev, buf, offset+1)) == 0)
        {
            return 0xffff;
        }
        offset += (elen+2);
    }
    return 0xffff;
}