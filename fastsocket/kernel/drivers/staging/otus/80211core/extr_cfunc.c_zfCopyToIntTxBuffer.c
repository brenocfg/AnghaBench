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
typedef  int /*<<< orphan*/  u8_t ;
typedef  size_t u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

void zfCopyToIntTxBuffer(zdev_t* dev, zbuf_t* buf, u8_t* src,
                         u16_t offset, u16_t length)
{
    u16_t i;

    for(i=0; i<length;i++)
    {
        zmw_tx_buf_writeb(dev, buf, offset+i, src[i]);
    }
}