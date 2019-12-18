#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u16_t ;

/* Variables and functions */

void copyToIntTxBuffer(zdev_t* dev, zbuf_t* buf, u8_t* src,
                         u16_t offset, u16_t length)
{
    u16_t i;

    for(i=0; i<length;i++)
    {
        //zmw_tx_buf_writeb(dev, buf, offset+i, src[i]);
        *(u8_t*)((u8_t*)buf->data+offset+i) = src[i];
    }
}