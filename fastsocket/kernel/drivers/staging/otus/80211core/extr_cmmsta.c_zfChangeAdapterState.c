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
typedef  int u8_t ;
struct TYPE_3__ {int adapterState; void* bChannelScan; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 void* FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  ZM_DEFAULT_SUPPORT_RATE_DISCONNECT ; 
 int /*<<< orphan*/  ZM_SCAN_MGR_SCAN_INTERNAL ; 
#define  ZM_STA_STATE_CONNECTED 130 
#define  ZM_STA_STATE_CONNECTING 129 
#define  ZM_STA_STATE_DISCONNECT 128 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfResetSupportRate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfScanMgrScanStop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u8_t zfChangeAdapterState(zdev_t* dev, u8_t newState)
{
    u8_t ret = TRUE;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    //if ( newState == wd->sta.adapterState )
    //{
    //    return FALSE;
    //}

    switch(newState)
    {
    case ZM_STA_STATE_DISCONNECT:
        zfResetSupportRate(dev, ZM_DEFAULT_SUPPORT_RATE_DISCONNECT);

        #if 1
            zfScanMgrScanStop(dev, ZM_SCAN_MGR_SCAN_INTERNAL);
        #else
            if ( wd->sta.bChannelScan )
            {
                /* stop the action of channel scanning */
                wd->sta.bChannelScan = FALSE;
                ret =  TRUE;
                break;
            }
        #endif

        break;
    case ZM_STA_STATE_CONNECTING:
        #if 1
            zfScanMgrScanStop(dev, ZM_SCAN_MGR_SCAN_INTERNAL);
        #else
            if ( wd->sta.bChannelScan )
            {
                /* stop the action of channel scanning */
                wd->sta.bChannelScan = FALSE;
                ret =  TRUE;
                break;
            }
        #endif

        break;
    case ZM_STA_STATE_CONNECTED:
        break;
    default:
        break;
    }

    //if ( ret )
    //{
        zmw_enter_critical_section(dev);
        wd->sta.adapterState = newState;
        zmw_leave_critical_section(dev);

        zm_debug_msg1("change adapter state = ", newState);
    //}

    return ret;
}