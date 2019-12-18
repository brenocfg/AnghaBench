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
struct TYPE_2__ {int /*<<< orphan*/ * p_addr_filter_count; } ;

/* Variables and functions */
 TYPE_1__ btm_ble_adv_filt_cb ; 
 int /*<<< orphan*/ * btm_ble_adv_filt_cb_ptr ; 
 int /*<<< orphan*/ * cmn_ble_adv_vsc_cb_ptr ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void btm_ble_adv_filter_cleanup(void)
{
    if (btm_ble_adv_filt_cb.p_addr_filter_count) {
        osi_free(btm_ble_adv_filt_cb.p_addr_filter_count);
        btm_ble_adv_filt_cb.p_addr_filter_count = NULL;
    }

#if BTM_DYNAMIC_MEMORY == TRUE
    osi_free(btm_ble_adv_filt_cb_ptr);
    btm_ble_adv_filt_cb_ptr = NULL;
    osi_free(cmn_ble_adv_vsc_cb_ptr);
    cmn_ble_adv_vsc_cb_ptr = NULL;
#endif
}