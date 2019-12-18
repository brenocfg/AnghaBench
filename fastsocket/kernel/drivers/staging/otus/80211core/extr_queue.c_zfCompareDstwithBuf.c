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
typedef  scalar_t__ u8_t ;
typedef  int u16_t ;

/* Variables and functions */
 scalar_t__ zmw_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfCompareDstwithBuf(zdev_t* dev, zbuf_t* buf, u8_t* addr)
{
    u16_t i;
    u8_t dst[6];

    for (i=0; i<6; i++)
    {
        dst[i] = zmw_buf_readb(dev, buf, i);
        if (dst[i] != addr[i])
        {
            return 1+i;
        }
    }

    return 0;
}