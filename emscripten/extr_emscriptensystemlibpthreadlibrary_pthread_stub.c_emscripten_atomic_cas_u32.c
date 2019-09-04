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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

uint32_t emscripten_atomic_cas_u32(void/*uint32_t*/ *addr, uint32_t oldVal, uint32_t newVal)
{
	uint32_t old = *(uint32_t*)addr;
	if (old == oldVal) *(uint32_t*)addr = newVal;
	return old;
}