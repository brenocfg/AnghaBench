#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u8_t ;
typedef  int u32_t ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; scalar_t__ connectState; int /*<<< orphan*/  connectTimer; scalar_t__ leapEnabled; } ;
struct TYPE_4__ {TYPE_1__ sta; int /*<<< orphan*/  tick; } ;

/* Variables and functions */
 int ZM_AUTH_ALGO_LEAP ; 
 int ZM_AUTH_ALGO_OPEN_SYSTEM ; 
 int ZM_AUTH_ALGO_SHARED_KEY ; 
 scalar_t__ ZM_STA_CONN_STATE_AUTH_OPEN ; 
 scalar_t__ ZM_STA_CONN_STATE_AUTH_SHARE_1 ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_AUTH ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfStaStartConnect(zdev_t* dev, u8_t bIsSharedKey)
{
    u32_t p1, p2;
    u8_t newConnState;

    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    /* p1_low = algorithm number, p1_high = transaction sequence number */
    if ( bIsSharedKey )
    {
        //wd->sta.connectState = ZM_STA_CONN_STATE_AUTH_SHARE_1;
        newConnState = ZM_STA_CONN_STATE_AUTH_SHARE_1;
        zm_debug_msg0("ZM_STA_CONN_STATE_AUTH_SHARE_1");
        p1 = ZM_AUTH_ALGO_SHARED_KEY;
    }
    else
    {
        //wd->sta.connectState = ZM_STA_CONN_STATE_AUTH_OPEN;
        newConnState = ZM_STA_CONN_STATE_AUTH_OPEN;
        zm_debug_msg0("ZM_STA_CONN_STATE_AUTH_OPEN");
        if( wd->sta.leapEnabled )
            p1 = ZM_AUTH_ALGO_LEAP;
        else
            p1 = ZM_AUTH_ALGO_OPEN_SYSTEM;
    }

    /* status code */
    p2 = 0x0;

    zmw_enter_critical_section(dev);
    wd->sta.connectTimer = wd->tick;
    wd->sta.connectState = newConnState;
    zmw_leave_critical_section(dev);

    /* send the 1st authentication frame */
    zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_AUTH, wd->sta.bssid, p1, p2, 0);

    return;
}