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
typedef  int u16_t ;

/* Variables and functions */
 int ZM_SUCCESS ; 
#define  ZM_WLAN_BLOCK_ACK_ACTION_FRAME 128 
 int /*<<< orphan*/  zfAggBlockAckActionFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t   zfAggProcessAction(zdev_t* dev, zbuf_t* buf)
{
    u16_t category;

    //zmw_get_wlan_dev(dev);

    //zmw_declare_for_critical_section();

    category = zmw_rx_buf_readb(dev, buf, 24);

    switch (category)
    {
    case ZM_WLAN_BLOCK_ACK_ACTION_FRAME:
        zfAggBlockAckActionFrame(dev, buf);
        break;

    }

    return ZM_SUCCESS;
}