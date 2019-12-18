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
typedef  int /*<<< orphan*/  __get_cpu_var ;

/* Variables and functions */

__attribute__((used)) static void tsc_bad(void *info)
{
	__get_cpu_var(cpu_tsc_khz) = 0;
}