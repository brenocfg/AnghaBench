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
typedef  int uint16_t ;

/* Variables and functions */

uint16_t emscripten_atomic_and_u16(void/*uint16_t*/ *addr, uint16_t val)
{
	uint16_t old = *(uint16_t*)addr;
	*(uint16_t*)addr = old & val;
	return old;
}