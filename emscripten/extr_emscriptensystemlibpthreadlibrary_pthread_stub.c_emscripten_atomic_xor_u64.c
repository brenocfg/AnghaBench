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
typedef  int uint64_t ;

/* Variables and functions */

uint64_t emscripten_atomic_xor_u64(void/*uint64_t*/ *addr, uint64_t val)
{
	uint64_t old = *(uint64_t*)addr;
	*(uint64_t*)addr = old ^ val;
	return old;
}