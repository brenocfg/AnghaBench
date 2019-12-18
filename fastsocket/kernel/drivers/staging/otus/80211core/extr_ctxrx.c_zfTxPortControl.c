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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_3__ {scalar_t__ adapterState; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_3 ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  ZM_PORT_DISABLED ; 
 int /*<<< orphan*/  ZM_PORT_ENABLED ; 
 scalar_t__ ZM_STA_STATE_DISCONNECT ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zm_msg0_tx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfTxPortControl(zdev_t* dev, zbuf_t* buf, u16_t port)
{
    zmw_get_wlan_dev(dev);

    if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
    {
        if ( wd->sta.adapterState == ZM_STA_STATE_DISCONNECT )
        {
            zm_msg0_tx(ZM_LV_3, "Packets dropped due to disconnect state");
            return ZM_PORT_DISABLED;
        }
    }

    return ZM_PORT_ENABLED;
}