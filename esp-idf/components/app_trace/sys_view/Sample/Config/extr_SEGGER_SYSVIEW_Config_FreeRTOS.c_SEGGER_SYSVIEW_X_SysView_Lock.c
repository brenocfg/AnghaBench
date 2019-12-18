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
typedef  int /*<<< orphan*/  esp_apptrace_tmo_t ;
struct TYPE_3__ {int int_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEGGER_LOCK_WAIT_TMO ; 
 int /*<<< orphan*/  esp_apptrace_lock_take (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_apptrace_tmo_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ s_sys_view_lock ; 

unsigned SEGGER_SYSVIEW_X_SysView_Lock(void)
{
    esp_apptrace_tmo_t tmo;
    esp_apptrace_tmo_init(&tmo, SEGGER_LOCK_WAIT_TMO);
    esp_apptrace_lock_take(&s_sys_view_lock, &tmo);
    // to be recursive save IRQ status on the stack of the caller to keep it from overwriting
    return s_sys_view_lock.int_state;
}