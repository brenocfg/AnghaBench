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
typedef  scalar_t__ u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zmw_rx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void zfRxBufferCopy(zdev_t*dev, zbuf_t* dst, zbuf_t* src,
                    u16_t dstOffset, u16_t srcOffset, u16_t length)
{
    u16_t i;

    for(i=0; i<length; i++)
    {
        zmw_rx_buf_writeb(dev, dst, dstOffset+i,
                             zmw_rx_buf_readb(dev, src, srcOffset+i));
    }
}