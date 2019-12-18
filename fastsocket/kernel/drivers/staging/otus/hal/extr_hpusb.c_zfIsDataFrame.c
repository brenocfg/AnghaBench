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

/* Variables and functions */
 int ZM_WLAN_DATA_FRAME ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u8_t zfIsDataFrame(zdev_t* dev, zbuf_t* buf)
{
    u8_t frameType;
    u8_t mpduInd;

    mpduInd = zmw_rx_buf_readb(dev, buf, zfwBufGetSize(dev, buf)-1);

    /* sinlge or First */
    if ((mpduInd & 0x30) == 0x00 || (mpduInd & 0x30) == 0x20)
    {
        frameType = zmw_rx_buf_readb(dev, buf, 12);
    }
    else
    {
        frameType = zmw_rx_buf_readb(dev, buf, 0);
    }

    if((frameType & 0xf) == ZM_WLAN_DATA_FRAME)
        return 1;
    else
        return 0;
}