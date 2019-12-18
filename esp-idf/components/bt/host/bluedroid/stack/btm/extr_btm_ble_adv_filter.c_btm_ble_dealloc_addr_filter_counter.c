#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bd_addr; scalar_t__ in_use; } ;
typedef  TYPE_1__ tBTM_BLE_PF_COUNT ;
struct TYPE_8__ {int /*<<< orphan*/  bda; } ;
typedef  TYPE_2__ tBLE_BD_ADDR ;
typedef  scalar_t__ UINT8 ;
struct TYPE_10__ {TYPE_1__* p_addr_filter_count; } ;
struct TYPE_9__ {scalar_t__ max_filter; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_BLE_PF_TYPE_ALL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_6__ btm_ble_adv_filt_cb ; 
 TYPE_4__ cmn_ble_adv_vsc_cb ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

BOOLEAN btm_ble_dealloc_addr_filter_counter(tBLE_BD_ADDR *p_bd_addr, UINT8 filter_type)
{
    UINT8               i;
    tBTM_BLE_PF_COUNT   *p_addr_filter = &btm_ble_adv_filt_cb.p_addr_filter_count[1];
    BOOLEAN             found = FALSE;

    if (BTM_BLE_PF_TYPE_ALL == filter_type && NULL == p_bd_addr) {
        memset(&btm_ble_adv_filt_cb.p_addr_filter_count[0], 0, sizeof(tBTM_BLE_PF_COUNT));
    }

    for (i = 0; i < cmn_ble_adv_vsc_cb.max_filter; i ++, p_addr_filter ++) {
        if ((p_addr_filter->in_use) && (NULL == p_bd_addr ||
                                        (NULL != p_bd_addr &&
                                         memcmp(p_bd_addr->bda, p_addr_filter->bd_addr, BD_ADDR_LEN) == 0))) {
            found = TRUE;
            memset(p_addr_filter, 0, sizeof(tBTM_BLE_PF_COUNT));

            if (NULL != p_bd_addr) {
                break;
            }
        }
    }
    return found;
}