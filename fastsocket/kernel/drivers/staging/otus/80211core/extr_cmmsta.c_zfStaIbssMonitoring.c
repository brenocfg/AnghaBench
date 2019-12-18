#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u8_t ;
typedef  scalar_t__ u16_t ;
struct zsPartnerNotifyEvent {int /*<<< orphan*/  peerMacAddr; int /*<<< orphan*/  bssid; } ;
struct TYPE_5__ {scalar_t__ oppositeCount; TYPE_1__* oppositeInfo; scalar_t__ bssid; scalar_t__ bChannelScan; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* zfcbIbssPartnerNotify ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct zsPartnerNotifyEvent*) ;TYPE_2__ sta; } ;
struct TYPE_4__ {scalar_t__ valid; scalar_t__ aliveCounter; scalar_t__* macAddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_EVENT_IBSS_MONITOR ; 
 scalar_t__ ZM_IBSS_PEER_ALIVE_COUNTER ; 
 scalar_t__ ZM_MAX_OPPOSITE_COUNT ; 
 int /*<<< orphan*/  ZM_TICK_IBSS_MONITOR ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_PROBEREQ ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct zsPartnerNotifyEvent*) ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfTimerSchedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfStaIbssMonitoring(zdev_t* dev, u8_t reset)
{
    u16_t i;
    u16_t oppositeCount;
    struct zsPartnerNotifyEvent event;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    //zm_debug_msg1("zfStaIbssMonitoring %d", wd->sta.oppositeCount);

    zmw_enter_critical_section(dev);

    if ( wd->sta.oppositeCount == 0 )
    {
        goto done;
    }

    if ( wd->sta.bChannelScan )
    {
        goto done;
    }

    oppositeCount = wd->sta.oppositeCount;

    for(i=0; i < ZM_MAX_OPPOSITE_COUNT; i++)
    {
        if ( oppositeCount == 0 )
        {
            break;
        }

        if ( reset )
        {
            wd->sta.oppositeInfo[i].valid = 0;
        }

        if ( wd->sta.oppositeInfo[i].valid == 0 )
        {
            continue;
        }

        oppositeCount--;

        if ( wd->sta.oppositeInfo[i].aliveCounter )
        {
            zm_debug_msg1("Setting alive to ", wd->sta.oppositeInfo[i].aliveCounter);

            zmw_leave_critical_section(dev);

            if ( wd->sta.oppositeInfo[i].aliveCounter != ZM_IBSS_PEER_ALIVE_COUNTER )
            {
                zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_PROBEREQ,
                              (u16_t*)wd->sta.oppositeInfo[i].macAddr, 1, 0, 0);
            }

            zmw_enter_critical_section(dev);
            wd->sta.oppositeInfo[i].aliveCounter--;
        }
        else
        {
            zm_debug_msg0("zfStaIbssMonitoring remove the peer station");
            zfMemoryCopy(event.bssid, (u8_t *)(wd->sta.bssid), 6);
            zfMemoryCopy(event.peerMacAddr, wd->sta.oppositeInfo[i].macAddr, 6);

            wd->sta.oppositeInfo[i].valid = 0;
            wd->sta.oppositeCount--;
            if (wd->zfcbIbssPartnerNotify != NULL)
            {
                zmw_leave_critical_section(dev);
                wd->zfcbIbssPartnerNotify(dev, 0, &event);
                zmw_enter_critical_section(dev);
            }
        }
    }

done:
    if ( reset == 0 )
    {
        zfTimerSchedule(dev, ZM_EVENT_IBSS_MONITOR, ZM_TICK_IBSS_MONITOR);
    }

    zmw_leave_critical_section(dev);
}