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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ esp_cpu_in_ocd_debug_mode () ; 
 int /*<<< orphan*/  setFirstBreakpoint (int /*<<< orphan*/ ) ; 

void esp_set_breakpoint_if_jtag(void *fn)
{
    if (esp_cpu_in_ocd_debug_mode()) {
        setFirstBreakpoint((uint32_t)fn);
    }
}