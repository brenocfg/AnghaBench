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
struct TYPE_2__ {int /*<<< orphan*/  sec_pending_q; int /*<<< orphan*/  page_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_lock_free () ; 
 int /*<<< orphan*/  btm_ble_sem_free () ; 
 TYPE_1__ btm_cb ; 
 int /*<<< orphan*/  btm_cb_ptr ; 
 int /*<<< orphan*/  fixed_queue_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free_func ; 

void btm_free(void)
{
    fixed_queue_free(btm_cb.page_queue, osi_free_func);
    fixed_queue_free(btm_cb.sec_pending_q, osi_free_func);
#if BTM_DYNAMIC_MEMORY
    FREE_AND_RESET(btm_cb_ptr);
#endif
#if BLE_INCLUDED == TRUE
    btm_ble_lock_free();
    btm_ble_sem_free();
#endif
}