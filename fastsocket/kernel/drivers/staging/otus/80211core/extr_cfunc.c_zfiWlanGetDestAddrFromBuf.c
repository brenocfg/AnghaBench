#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_2__ {scalar_t__ wlanMode; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u8_t zfiWlanGetDestAddrFromBuf(zdev_t *dev, zbuf_t *buf, u16_t *macAddr)
{
#ifdef ZM_ENABLE_NATIVE_WIFI
    zmw_get_wlan_dev(dev);

    if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
    {
        /* DA */
        macAddr[0] = zmw_tx_buf_readh(dev, buf, 16);
        macAddr[1] = zmw_tx_buf_readh(dev, buf, 18);
        macAddr[2] = zmw_tx_buf_readh(dev, buf, 20);
    }
    else if ( wd->wlanMode == ZM_MODE_IBSS )
    {
        /* DA */
        macAddr[0] = zmw_tx_buf_readh(dev, buf, 4);
        macAddr[1] = zmw_tx_buf_readh(dev, buf, 6);
        macAddr[2] = zmw_tx_buf_readh(dev, buf, 8);
    }
    else if ( wd->wlanMode == ZM_MODE_AP )
    {
        /* DA */
        macAddr[0] = zmw_tx_buf_readh(dev, buf, 4);
        macAddr[1] = zmw_tx_buf_readh(dev, buf, 6);
        macAddr[2] = zmw_tx_buf_readh(dev, buf, 8);
    }
    else
    {
        return 1;
    }
#else
    /* DA */
    macAddr[0] = zmw_tx_buf_readh(dev, buf, 0);
    macAddr[1] = zmw_tx_buf_readh(dev, buf, 2);
    macAddr[2] = zmw_tx_buf_readh(dev, buf, 4);
#endif

    return 0;
}