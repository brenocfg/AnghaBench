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
 int /*<<< orphan*/  BTE_InitStack () ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  bluedroid_init_done_cb () ; 
 int /*<<< orphan*/  bta_sys_init () ; 
 int /*<<< orphan*/  btu_init_core () ; 

void btu_task_start_up(void *param)
{
    UNUSED(param);
    /* Initialize the mandatory core stack control blocks
       (BTU, BTM, L2CAP, and SDP)
     */
    btu_init_core();

    /* Initialize any optional stack components */
    BTE_InitStack();

#if (defined(BTA_INCLUDED) && BTA_INCLUDED == TRUE)
    bta_sys_init();
#endif

    // Inform the bt jni thread initialization is ok.
    // btif_transfer_context(btif_init_ok, 0, NULL, 0, NULL);
#if(defined(BT_APP_DEMO) && BT_APP_DEMO == TRUE)
    if (bluedroid_init_done_cb) {
        bluedroid_init_done_cb();
    }
#endif
}