#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  in_use; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_1__ tBTM_BLE_PF_COUNT ;
typedef  scalar_t__ UINT8 ;
struct TYPE_7__ {TYPE_1__* p_addr_filter_count; } ;
struct TYPE_6__ {scalar_t__ max_filter; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ btm_ble_adv_filt_cb ; 
 TYPE_2__ cmn_ble_adv_vsc_cb ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  na_bda ; 

tBTM_BLE_PF_COUNT *btm_ble_alloc_addr_filter_counter(BD_ADDR bd_addr)
{
    UINT8               i;
    tBTM_BLE_PF_COUNT   *p_addr_filter = &btm_ble_adv_filt_cb.p_addr_filter_count[1];

    for (i = 0; i < cmn_ble_adv_vsc_cb.max_filter; i ++, p_addr_filter ++) {
        if (memcmp(na_bda, p_addr_filter->bd_addr, BD_ADDR_LEN) == 0) {
            memcpy(p_addr_filter->bd_addr, bd_addr, BD_ADDR_LEN);
            p_addr_filter->in_use = TRUE;
            return p_addr_filter;
        }
    }
    return NULL;
}