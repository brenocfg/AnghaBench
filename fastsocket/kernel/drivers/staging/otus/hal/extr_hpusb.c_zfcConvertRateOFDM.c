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
typedef  int u32_t ;

/* Variables and functions */
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u32_t zfcConvertRateOFDM(zdev_t* dev, zbuf_t* buf)
{
    // What's the default value??
    u32_t MCS = 0;

    switch(zmw_rx_buf_readb(dev, buf, 0)& 0xf)
    {
        case 0xb:
            MCS = 0x4;
            break;
        case 0xf:
            MCS = 0x5;
            break;
        case 0xa:
            MCS = 0x6;
            break;
        case 0xe:
            MCS = 0x7;
            break;
        case 0x9:
            MCS = 0x8;
            break;
        case 0xd:
            MCS = 0x9;
            break;
        case 0x8:
            MCS = 0xa;
            break;
        case 0xc:
            MCS = 0xb;
            break;
    }
    return MCS;
}