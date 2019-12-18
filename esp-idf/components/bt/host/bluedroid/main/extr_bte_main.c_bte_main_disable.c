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
 int /*<<< orphan*/  BTU_ShutDown () ; 
 int /*<<< orphan*/  hci_shut_down () ; 

__attribute__((used)) static void bte_main_disable(void)
{
    /*
        APPL_TRACE_DEBUG("%s", __FUNCTION__);

        module_shut_down(get_module(HCI_MODULE));
        module_shut_down(get_module(BTSNOOP_MODULE));
    */

    hci_shut_down();

    BTU_ShutDown();
}