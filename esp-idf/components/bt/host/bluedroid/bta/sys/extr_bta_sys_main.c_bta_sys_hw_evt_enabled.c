#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hw_module; } ;
typedef  TYPE_1__ tBTA_SYS_HW_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_EVENT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_DeviceReset (int /*<<< orphan*/ *) ; 

void bta_sys_hw_evt_enabled(tBTA_SYS_HW_MSG *p_sys_hw_msg)
{
    APPL_TRACE_EVENT("bta_sys_hw_evt_enabled for %i\n", p_sys_hw_msg->hw_module);
    BTM_DeviceReset( NULL );
}