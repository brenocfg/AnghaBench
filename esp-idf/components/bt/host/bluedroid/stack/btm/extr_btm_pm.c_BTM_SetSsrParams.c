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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_5__ {scalar_t__ state; void* min_loc_to; void* min_rmt_to; void* max_lat; } ;
typedef  TYPE_2__ tBTM_PM_MCB ;
typedef  void* UINT16 ;
struct TYPE_6__ {TYPE_2__* pm_mode_db; TYPE_1__* acl_db; } ;
struct TYPE_4__ {int /*<<< orphan*/  hci_handle; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CMD_STORED ; 
 int /*<<< orphan*/  BTM_ILLEGAL_ACTION ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 scalar_t__ BTM_PM_STS_ACTIVE ; 
 scalar_t__ BTM_PM_STS_SNIFF ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 int MAX_L2CAP_LINKS ; 
 TYPE_3__ btm_cb ; 
 int btm_pm_find_acl_ind (int /*<<< orphan*/ ) ; 
 scalar_t__ btsnd_hcic_sniff_sub_rate (int /*<<< orphan*/ ,void*,void*,void*) ; 

tBTM_STATUS BTM_SetSsrParams (BD_ADDR remote_bda, UINT16 max_lat,
                              UINT16 min_rmt_to, UINT16 min_loc_to)
{
#if (BTM_SSR_INCLUDED == TRUE)
    int acl_ind;
    tBTM_PM_MCB *p_cb;

    if ( (acl_ind = btm_pm_find_acl_ind(remote_bda)) == MAX_L2CAP_LINKS) {
        return (BTM_UNKNOWN_ADDR);
    }

    if (BTM_PM_STS_ACTIVE == btm_cb.pm_mode_db[acl_ind].state ||
            BTM_PM_STS_SNIFF == btm_cb.pm_mode_db[acl_ind].state) {
        if (btsnd_hcic_sniff_sub_rate(btm_cb.acl_db[acl_ind].hci_handle, max_lat,
                                      min_rmt_to, min_loc_to)) {
            return BTM_SUCCESS;
        } else {
            return BTM_NO_RESOURCES;
        }
    }
    p_cb = &btm_cb.pm_mode_db[acl_ind];
    p_cb->max_lat       = max_lat;
    p_cb->min_rmt_to    = min_rmt_to;
    p_cb->min_loc_to    = min_loc_to;
    return BTM_CMD_STORED;
#else
    return BTM_ILLEGAL_ACTION;
#endif  // BTM_SSR_INCLUDED
}