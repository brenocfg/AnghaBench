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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

uint8_t emscripten_atomic_cas_u8(void/*uint8_t*/ *addr, uint8_t oldVal, uint8_t newVal)
{
	uint8_t old = *(uint8_t*)addr;
	if (old == oldVal) *(uint8_t*)addr = newVal;
	return old;
}