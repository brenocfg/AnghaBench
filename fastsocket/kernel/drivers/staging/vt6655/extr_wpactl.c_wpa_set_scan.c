#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct viawget_wpa_param {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  bLinkPass; } ;
typedef  TYPE_1__* PSDevice ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  BSSvClearBSSList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_CMD_BSSID_SCAN ; 
 int /*<<< orphan*/  bScheduleCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wpa_set_scan(PSDevice pDevice,
				     struct viawget_wpa_param *param)
{
	int ret = 0;

    spin_lock_irq(&pDevice->lock);
    BSSvClearBSSList((HANDLE)pDevice, pDevice->bLinkPass);
    bScheduleCommand((HANDLE) pDevice, WLAN_CMD_BSSID_SCAN, NULL);
    spin_unlock_irq(&pDevice->lock);

    return ret;
}