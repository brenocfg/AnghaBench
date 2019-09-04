#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * cpu_flag_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int /*<<< orphan*/  color_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ state ; 

__attribute__((used)) static void print_cpu_name(void)
{
    if (state.cpu_flag_name) {
        color_printf(COLOR_YELLOW, "%s:\n", state.cpu_flag_name);
        state.cpu_flag_name = NULL;
    }
}