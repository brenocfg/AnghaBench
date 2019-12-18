#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  BTC_TASK_PINNED_TO_CORE ; 
 int /*<<< orphan*/  BTC_TASK_PRIO ; 
 int /*<<< orphan*/  BTC_TASK_STACK_SIZE ; 
 int BT_STATUS_NOMEM ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  btc_adv_list_init () ; 
 int /*<<< orphan*/  btc_gap_callback_init () ; 
 scalar_t__ btc_init_mem () ; 
 int /*<<< orphan*/ * btc_thread ; 
 int /*<<< orphan*/ * osi_thread_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int btc_init(void)
{
    btc_thread = osi_thread_create("BTC_TASK", BTC_TASK_STACK_SIZE, BTC_TASK_PRIO, BTC_TASK_PINNED_TO_CORE, 2);
    if (btc_thread == NULL) {
        return BT_STATUS_NOMEM;
    }

#if BTC_DYNAMIC_MEMORY
    if (btc_init_mem() != BT_STATUS_SUCCESS){
        return BT_STATUS_NOMEM;
    }
#endif

#if (BLE_INCLUDED == TRUE)
    btc_gap_callback_init();
#endif  ///BLE_INCLUDED == TRUE

#if SCAN_QUEUE_CONGEST_CHECK
    btc_adv_list_init();
#endif
    /* TODO: initial the profile_tab */
    return BT_STATUS_SUCCESS;
}