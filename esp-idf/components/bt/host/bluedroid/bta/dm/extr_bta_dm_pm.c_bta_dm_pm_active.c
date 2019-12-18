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
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ tBTM_PM_PWR_MD ;
typedef  int /*<<< orphan*/  pm ;
struct TYPE_5__ {int /*<<< orphan*/  pm_id; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_PM_MD_ACTIVE ; 
 int /*<<< orphan*/  BTM_SetPowerMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__ bta_dm_cb ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void bta_dm_pm_active(BD_ADDR peer_addr)
{
    tBTM_PM_PWR_MD  pm;

    memset( (void *)&pm, 0, sizeof(pm));

    /* switch to active mode */
    pm.mode = BTM_PM_MD_ACTIVE;
    BTM_SetPowerMode (bta_dm_cb.pm_id, peer_addr, &pm);
}