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
typedef  size_t u8_t ;
typedef  int u16_t ;
struct TYPE_6__ {TYPE_1__* entity; } ;
struct TYPE_7__ {size_t ibssPSDataCount; size_t ibssPrevPSDataCount; int /*<<< orphan*/ * ibssPSDataQueue; TYPE_2__ staPSList; } ;
struct TYPE_8__ {scalar_t__ wlanMode; TYPE_3__ sta; } ;
struct TYPE_5__ {scalar_t__ bDataQueued; scalar_t__ macAddr; scalar_t__ bUsed; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ZM_EXTERNAL_ALLOC_BUF ; 
 size_t ZM_MAX_PS_STA ; 
 scalar_t__ ZM_MODE_IBSS ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_ATIM ; 
 TYPE_4__* wd ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTxSendEth (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfStaIbssPSSend(zdev_t* dev)
{
    u8_t   i;
    u16_t  bcastAddr[3] = {0xffff, 0xffff, 0xffff};

    zmw_get_wlan_dev(dev);

    if ( !zfStaIsConnected(dev) )
    {
        return ;
    }

    if ( wd->wlanMode != ZM_MODE_IBSS )
    {
        return ;
    }

    for(i=0; i<ZM_MAX_PS_STA; i++)
    {
        if ( wd->sta.staPSList.entity[i].bDataQueued )
        {
            if ( i == 0 )
            {
                zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_ATIM,
                              bcastAddr,
                              0, 0, 0);
            }
            else if ( wd->sta.staPSList.entity[i].bUsed )
            {
                // Send ATIM to prevent the peer to go to sleep
                zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_ATIM,
                              (u16_t*) wd->sta.staPSList.entity[i].macAddr,
                              0, 0, 0);
            }

            wd->sta.staPSList.entity[i].bDataQueued = FALSE;
        }
    }

    for(i=0; i<wd->sta.ibssPSDataCount; i++)
    {
        zfTxSendEth(dev, wd->sta.ibssPSDataQueue[i], 0,
                    ZM_EXTERNAL_ALLOC_BUF, 0);
    }

    wd->sta.ibssPrevPSDataCount = wd->sta.ibssPSDataCount;
    wd->sta.ibssPSDataCount = 0;
}