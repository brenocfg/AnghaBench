#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_6__ {scalar_t__ count; TYPE_1__* entity; } ;
struct TYPE_7__ {scalar_t__ powerSaveMode; int /*<<< orphan*/  staPSDataCount; int /*<<< orphan*/ ** staPSDataQueue; int /*<<< orphan*/  ibssPSDataCount; int /*<<< orphan*/ ** ibssPSDataQueue; TYPE_2__ staPSList; } ;
struct TYPE_8__ {scalar_t__ wlanMode; TYPE_3__ sta; } ;
struct TYPE_5__ {void* bDataQueued; int /*<<< orphan*/  macAddr; } ;

/* Variables and functions */
 void* TRUE ; 
 scalar_t__ ZM_IS_MULTICAST_OR_BROADCAST (int /*<<< orphan*/ *) ; 
 int ZM_MAX_PS_STA ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_STA_PS_NONE ; 
 int ZM_WLAN_HEADER_A1_OFFSET ; 
 TYPE_4__* wd ; 
 scalar_t__ zfMemoryIsEqual (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u8_t zfStaIbssPSQueueData(zdev_t* dev, zbuf_t* buf)
{
    u8_t   i;
    u16_t  da[3];

    zmw_get_wlan_dev(dev);

    if ( !zfStaIsConnected(dev) )
    {
        return 0;
    }

    if ( wd->wlanMode != ZM_MODE_IBSS )
    {
        return 0;
    }

    if ( wd->sta.staPSList.count == 0 && wd->sta.powerSaveMode <= ZM_STA_PS_NONE )
    {
        return 0;
    }

    /* DA */
#ifdef ZM_ENABLE_NATIVE_WIFI
    da[0] = zmw_tx_buf_readh(dev, buf, ZM_WLAN_HEADER_A1_OFFSET);
    da[1] = zmw_tx_buf_readh(dev, buf, ZM_WLAN_HEADER_A1_OFFSET + 2);
    da[2] = zmw_tx_buf_readh(dev, buf, ZM_WLAN_HEADER_A1_OFFSET + 4);
#else
    da[0] = zmw_tx_buf_readh(dev, buf, 0);
    da[1] = zmw_tx_buf_readh(dev, buf, 2);
    da[2] = zmw_tx_buf_readh(dev, buf, 4);
#endif

    if ( ZM_IS_MULTICAST_OR_BROADCAST(da) )
    {
        wd->sta.staPSList.entity[0].bDataQueued = TRUE;
        wd->sta.ibssPSDataQueue[wd->sta.ibssPSDataCount++] = buf;
        return 1;
    }

    // Unicast packet...

    for(i=1; i<ZM_MAX_PS_STA; i++)
    {
        if ( zfMemoryIsEqual(wd->sta.staPSList.entity[i].macAddr,
                             (u8_t*) da, 6) )
        {
            wd->sta.staPSList.entity[i].bDataQueued = TRUE;
            wd->sta.ibssPSDataQueue[wd->sta.ibssPSDataCount++] = buf;

            return 1;
        }
    }

#if 0
    if ( wd->sta.powerSaveMode > ZM_STA_PS_NONE )
    {
        wd->sta.staPSDataQueue[wd->sta.staPSDataCount++] = buf;

        return 1;
    }
#endif

    return 0;
}