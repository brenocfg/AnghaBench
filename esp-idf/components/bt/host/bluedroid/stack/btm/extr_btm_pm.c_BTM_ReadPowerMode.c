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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_PM_MODE ;
struct TYPE_4__ {TYPE_1__* pm_mode_db; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 int MAX_L2CAP_LINKS ; 
 TYPE_2__ btm_cb ; 
 int btm_pm_find_acl_ind (int /*<<< orphan*/ ) ; 

tBTM_STATUS BTM_ReadPowerMode (BD_ADDR remote_bda, tBTM_PM_MODE *p_mode)
{
    int acl_ind;

    if ( (acl_ind = btm_pm_find_acl_ind(remote_bda)) == MAX_L2CAP_LINKS) {
        return (BTM_UNKNOWN_ADDR);
    }

    *p_mode = btm_cb.pm_mode_db[acl_ind].state;
    return BTM_SUCCESS;
}