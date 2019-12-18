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
struct TYPE_3__ {scalar_t__ connectState; scalar_t__ connectTimer; int failCntOfReasso; scalar_t__ authMode; int /*<<< orphan*/  bssid; int /*<<< orphan*/  connectTimeoutCount; scalar_t__ connectByReasso; } ;
struct TYPE_4__ {scalar_t__ wlanMode; scalar_t__ tick; TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ZM_AUTH_MODE_AUTO ; 
 scalar_t__ ZM_INTERVAL_CONNECT_TIMEOUT ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_DISCONNECT_TIMEOUT ; 
 scalar_t__ ZM_STA_CONN_STATE_ASSOCIATE ; 
 scalar_t__ ZM_STA_CONN_STATE_AUTH_OPEN ; 
 scalar_t__ ZM_STA_CONN_STATE_AUTH_SHARE_1 ; 
 scalar_t__ ZM_STA_CONN_STATE_AUTH_SHARE_2 ; 
 scalar_t__ ZM_STA_CONN_STATE_NONE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfStaConnectFail (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfStaIsConnecting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfStaCheckConnectTimeout(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    if ( wd->wlanMode != ZM_MODE_INFRASTRUCTURE )
    {
        return;
    }

    if ( !zfStaIsConnecting(dev) )
    {
        return;
    }

    zmw_enter_critical_section(dev);
    if ( (wd->sta.connectState == ZM_STA_CONN_STATE_AUTH_OPEN)||
         (wd->sta.connectState == ZM_STA_CONN_STATE_AUTH_SHARE_1)||
         (wd->sta.connectState == ZM_STA_CONN_STATE_AUTH_SHARE_2)||
         (wd->sta.connectState == ZM_STA_CONN_STATE_ASSOCIATE) )
    {
        if ( (wd->tick - wd->sta.connectTimer) > ZM_INTERVAL_CONNECT_TIMEOUT )
        {
            if ( wd->sta.connectByReasso )
            {
                wd->sta.failCntOfReasso++;
                if ( wd->sta.failCntOfReasso > 2 )
                {
                    wd->sta.connectByReasso = FALSE;
                }
            }

            wd->sta.connectState = ZM_STA_CONN_STATE_NONE;
            zm_debug_msg1("connect timeout, state = ", wd->sta.connectState);
            //zfiWlanDisable(dev);
            goto failed;
        }
    }

    zmw_leave_critical_section(dev);
    return;

failed:
    zmw_leave_critical_section(dev);
    if(wd->sta.authMode == ZM_AUTH_MODE_AUTO)
	{ // Fix some AP not send authentication failed message to sta and lead to connect timeout !
            wd->sta.connectTimeoutCount++;
	}
    zfStaConnectFail(dev, ZM_STATUS_MEDIA_DISCONNECT_TIMEOUT, wd->sta.bssid, 2);
    return;
}