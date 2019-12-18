#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;
struct zsRcCell {size_t currentRateIndex; int /*<<< orphan*/  currentRate; int /*<<< orphan*/  lastTime; scalar_t__ lasttxCount; scalar_t__ txCount; scalar_t__ failCount; int /*<<< orphan*/ * operationRateSet; } ;
struct TYPE_2__ {int /*<<< orphan*/  tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zm_msg1_tx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfRateCtrlNextLowerRate(zdev_t* dev, struct zsRcCell* rcCell)
{
    zmw_get_wlan_dev(dev);
    if (rcCell->currentRateIndex > 0)
    {
        rcCell->currentRateIndex--;
        rcCell->currentRate = rcCell->operationRateSet[rcCell->currentRateIndex];
    }
    zm_msg1_tx(ZM_LV_0, "Lower Tx Rate=", rcCell->currentRate);
    //DbgPrint("Lower Tx Rate=%d", rcCell->currentRate);
    rcCell->failCount = rcCell->txCount = 0;
    rcCell->lasttxCount = 0;
    rcCell->lastTime  = wd->tick;
    return rcCell->currentRate;
}