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
 int /*<<< orphan*/  btc_adv_list_deinit () ; 
 int /*<<< orphan*/  btc_deinit_mem () ; 
 int /*<<< orphan*/ * btc_thread ; 
 int /*<<< orphan*/  osi_thread_free (int /*<<< orphan*/ *) ; 

void btc_deinit(void)
{
#if BTC_DYNAMIC_MEMORY
    btc_deinit_mem();
#endif

    osi_thread_free(btc_thread);
    btc_thread = NULL;

#if SCAN_QUEUE_CONGEST_CHECK
    btc_adv_list_deinit();
#endif
}