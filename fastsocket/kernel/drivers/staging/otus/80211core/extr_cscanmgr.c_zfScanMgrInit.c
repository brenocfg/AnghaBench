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
struct TYPE_4__ {int scanStartDelay; int /*<<< orphan*/  currScanType; scalar_t__* scanReqs; } ;
struct TYPE_5__ {TYPE_1__ scanMgr; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_SCAN_MGR_SCAN_NONE ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfScanMgrInit(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    wd->sta.scanMgr.scanReqs[0] = 0;
    wd->sta.scanMgr.scanReqs[1] = 0;

    wd->sta.scanMgr.currScanType = ZM_SCAN_MGR_SCAN_NONE;
    wd->sta.scanMgr.scanStartDelay = 3;
    //wd->sta.scanMgr.scanStartDelay = 0;
}