#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct viawget_wpa_param {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; scalar_t__ bLinkPass; TYPE_1__* pMgmt; } ;
struct TYPE_4__ {int /*<<< orphan*/  abyCurrBSSID; } ;
typedef  TYPE_1__* PSMgmtObject ;
typedef  TYPE_2__* PSDevice ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_CMD_DISASSOCIATE ; 
 int /*<<< orphan*/  bScheduleCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wpa_set_disassociate(PSDevice pDevice,
				     struct viawget_wpa_param *param)
{
    PSMgmtObject    pMgmt = pDevice->pMgmt;
	int ret = 0;

    spin_lock_irq(&pDevice->lock);
    if (pDevice->bLinkPass) {
        if (!memcmp(param->addr, pMgmt->abyCurrBSSID, 6))
            bScheduleCommand((HANDLE)pDevice, WLAN_CMD_DISASSOCIATE, NULL);
    }
    spin_unlock_irq(&pDevice->lock);

    return ret;
}