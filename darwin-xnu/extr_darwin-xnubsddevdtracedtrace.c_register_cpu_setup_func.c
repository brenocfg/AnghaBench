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
typedef  int /*<<< orphan*/  cpu_setup_func_t ;

/* Variables and functions */

void
register_cpu_setup_func(cpu_setup_func_t *ignore1, void *ignore2)
{
#pragma unused(ignore1,ignore2)
}