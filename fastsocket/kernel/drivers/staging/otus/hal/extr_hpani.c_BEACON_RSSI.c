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
struct TYPE_4__ {int /*<<< orphan*/  ns_avgbrssi; } ;
struct TYPE_5__ {TYPE_1__ ast_nodestats; } ;
struct zsHpPriv {TYPE_2__ stats; } ;
typedef  int /*<<< orphan*/  s32_t ;
struct TYPE_6__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_HAL_EP_RND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZM_HAL_RSSI_EP_MULTIPLIER ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

s32_t BEACON_RSSI(zdev_t* dev)
{
    s32_t rssi;
    struct zsHpPriv *HpPriv;

    zmw_get_wlan_dev(dev);
    HpPriv = (struct zsHpPriv*)wd->hpPrivate;

    rssi = ZM_HAL_EP_RND(HpPriv->stats.ast_nodestats.ns_avgbrssi, ZM_HAL_RSSI_EP_MULTIPLIER);

    return rssi;
}