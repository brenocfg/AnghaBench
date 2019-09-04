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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  emscripten_atomic_or_u64 (void*,int /*<<< orphan*/ ) ; 

uint64_t _emscripten_atomic_fetch_and_or_u64(void *addr, uint64_t val)
{
	return emscripten_atomic_or_u64(addr, val);
}