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
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_SUCCESS ; 
#define  ZM_WLAN_ADDBA_REQUEST_FRAME 130 
#define  ZM_WLAN_ADDBA_RESPONSE_FRAME 129 
#define  ZM_WLAN_DELBA_FRAME 128 
 int /*<<< orphan*/  zfAggRecvAddbaRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfAggRecvAddbaResponse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfAggRecvDelba (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_msg0_agg (int /*<<< orphan*/ ,char*) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t   zfAggBlockAckActionFrame(zdev_t* dev, zbuf_t* buf)
{
    u8_t action;

    //zmw_get_wlan_dev(dev);

    //zmw_declare_for_critical_section();

    action = zmw_rx_buf_readb(dev, buf, 25);
#ifdef ZM_ENABLE_AGGREGATION
    switch (action)
    {
    case ZM_WLAN_ADDBA_REQUEST_FRAME:
        zm_msg0_agg(ZM_LV_0, "Received BA Action frame is ADDBA request");
        zfAggRecvAddbaRequest(dev, buf);
        break;
    case ZM_WLAN_ADDBA_RESPONSE_FRAME:
        zm_msg0_agg(ZM_LV_0, "Received BA Action frame is ADDBA response");
        zfAggRecvAddbaResponse(dev, buf);
        break;
    case ZM_WLAN_DELBA_FRAME:
        zfAggRecvDelba(dev, buf);
        break;
    }
#endif
    return ZM_SUCCESS;
}