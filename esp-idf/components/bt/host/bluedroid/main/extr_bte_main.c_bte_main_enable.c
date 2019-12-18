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
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTU_StartUp () ; 
 scalar_t__ hci_start_up () ; 

__attribute__((used)) static void bte_main_enable(void)
{
    APPL_TRACE_DEBUG("Enable HCI\n");
    if (hci_start_up()) {
        APPL_TRACE_ERROR("Start HCI Host Layer Failure\n");
        return;
    }

    //Now Test Case Not Supported BTU
    BTU_StartUp();
}