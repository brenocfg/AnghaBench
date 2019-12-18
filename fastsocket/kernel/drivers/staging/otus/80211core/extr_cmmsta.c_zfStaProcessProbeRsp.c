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
struct zsAdditionInfo {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bChannelScan; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfProcessProbeRsp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsAdditionInfo*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfStaProcessProbeRsp(zdev_t* dev, zbuf_t* buf, struct zsAdditionInfo* AddInfo)
{
    /* return if not channel scan */
    // Probe response is sent with unicast. Is this required?
    // IBSS would send probe request and the code below would prevent
    // the probe response from handling.
    #if 0
    zmw_get_wlan_dev(dev);

    if ( !wd->sta.bChannelScan )
    {
        return;
    }
    #endif

    zfProcessProbeRsp(dev, buf, AddInfo);
}