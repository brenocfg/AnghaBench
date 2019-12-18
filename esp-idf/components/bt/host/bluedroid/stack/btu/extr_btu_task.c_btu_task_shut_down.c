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
 int /*<<< orphan*/  BTE_DeinitStack () ; 
 int /*<<< orphan*/  bta_sys_free () ; 
 int /*<<< orphan*/  btu_free_core () ; 

void btu_task_shut_down(void)
{
#if (defined(BTA_INCLUDED) && BTA_INCLUDED == TRUE)
    bta_sys_free();
#endif
    BTE_DeinitStack();

    btu_free_core();
}