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

void esp_clear_watchpoint(int no)
{
    //Setting a dbreakc register to 0 makes it trigger on neither load nor store, effectively disabling it.
    int dbreakc = 0;
    if (no == 0) {
        asm volatile(
            "wsr.dbreakc0 %0\n" \
            ::"r"(dbreakc));
    } else {
        asm volatile(
            "wsr.dbreakc1 %0\n" \
            ::"r"(dbreakc));
    }
}