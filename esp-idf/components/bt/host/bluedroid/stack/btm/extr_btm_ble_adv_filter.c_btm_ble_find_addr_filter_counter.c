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
typedef  struct TYPE_9__   TYPE_3__ ;
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

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 TYPE_6__ btm_ble_adv_filt_cb ; 
 TYPE_3__ cmn_ble_adv_vsc_cb ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tBTM_BLE_PF_COUNT *btm_ble_find_addr_filter_counter(tBLE_BD_ADDR *p_le_bda)
{
    UINT8               i;
    tBTM_BLE_PF_COUNT   *p_addr_filter = &btm_ble_adv_filt_cb.p_addr_filter_count[1];

    if (p_le_bda == NULL) {
        return &btm_ble_adv_filt_cb.p_addr_filter_count[0];
    }

    for (i = 0; i < cmn_ble_adv_vsc_cb.max_filter; i ++, p_addr_filter ++) {
        if (p_addr_filter->in_use &&
                memcmp(p_le_bda->bda, p_addr_filter->bd_addr, BD_ADDR_LEN) == 0) {
            return p_addr_filter;
        }
    }
    return NULL;
}