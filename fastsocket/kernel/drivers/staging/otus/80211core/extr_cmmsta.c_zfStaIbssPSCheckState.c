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
struct TYPE_6__ {scalar_t__ count; TYPE_1__* entity; } ;
struct TYPE_7__ {TYPE_2__ staPSList; scalar_t__ bssid; } ;
struct TYPE_8__ {scalar_t__ wlanMode; TYPE_3__ sta; } ;
struct TYPE_5__ {int* macAddr; void* bDataQueued; void* bUsed; } ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int ZM_BIT_4 ; 
 int ZM_MAX_PS_STA ; 
 scalar_t__ ZM_MODE_IBSS ; 
 int /*<<< orphan*/  ZM_WLAN_HEADER_A2_OFFSET ; 
 int /*<<< orphan*/  ZM_WLAN_HEADER_A3_OFFSET ; 
 TYPE_4__* wd ; 
 int /*<<< orphan*/  zfCopyFromRxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zfRxBufferEqualToStr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfStaIbssPSCheckState(zdev_t* dev, zbuf_t* buf)
{
    u8_t   i, frameCtrl;

    zmw_get_wlan_dev(dev);

    if ( !zfStaIsConnected(dev) )
    {
        return;
    }

    if ( wd->wlanMode != ZM_MODE_IBSS )
    {
        return ;
    }

    /* check BSSID */
    if ( !zfRxBufferEqualToStr(dev, buf, (u8_t*) wd->sta.bssid,
                               ZM_WLAN_HEADER_A3_OFFSET, 6) )
    {
        return;
    }

    frameCtrl = zmw_rx_buf_readb(dev, buf, 1);

    /* check power management bit */
    if ( frameCtrl & ZM_BIT_4 )
    {
        for(i=1; i<ZM_MAX_PS_STA; i++)
        {
            if ( !wd->sta.staPSList.entity[i].bUsed )
            {
                continue;
            }

            /* check source address */
            if ( zfRxBufferEqualToStr(dev, buf,
                                      wd->sta.staPSList.entity[i].macAddr,
                                      ZM_WLAN_HEADER_A2_OFFSET, 6) )
            {
                return;
            }
        }

        for(i=1; i<ZM_MAX_PS_STA; i++)
        {
            if ( !wd->sta.staPSList.entity[i].bUsed )
            {
                wd->sta.staPSList.entity[i].bUsed = TRUE;
                wd->sta.staPSList.entity[i].bDataQueued = FALSE;
                break;
            }
        }

        if ( i == ZM_MAX_PS_STA )
        {
            /* STA list is full */
            return;
        }

        zfCopyFromRxBuffer(dev, buf, wd->sta.staPSList.entity[i].macAddr,
                           ZM_WLAN_HEADER_A2_OFFSET, 6);

        if ( wd->sta.staPSList.count == 0 )
        {
            // enable ATIM window
            //zfEnableAtimWindow(dev);
        }

        wd->sta.staPSList.count++;
    }
    else if ( wd->sta.staPSList.count )
    {
        for(i=1; i<ZM_MAX_PS_STA; i++)
        {
            if ( wd->sta.staPSList.entity[i].bUsed )
            {
                if ( zfRxBufferEqualToStr(dev, buf,
                                          wd->sta.staPSList.entity[i].macAddr,
                                          ZM_WLAN_HEADER_A2_OFFSET, 6) )
                {
                    wd->sta.staPSList.entity[i].bUsed = FALSE;
                    wd->sta.staPSList.count--;

                    if ( wd->sta.staPSList.entity[i].bDataQueued )
                    {
                        /* send queued data */
                    }
                }
            }
        }

        if ( wd->sta.staPSList.count == 0 )
        {
            /* disable ATIM window */
            //zfDisableAtimWindow(dev);
        }

    }
}