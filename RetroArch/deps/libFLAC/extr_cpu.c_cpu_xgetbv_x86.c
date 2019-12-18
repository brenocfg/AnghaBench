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
 int /*<<< orphan*/  _xgetbv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
cpu_xgetbv_x86(void)
{
#if (defined _MSC_VER || defined __INTEL_COMPILER) && FLAC__HAS_X86INTRIN && FLAC__AVX_SUPPORTED
	return (uint32_t)_xgetbv(0);
#elif defined __GNUC__
	uint32_t lo, hi;
	__asm__ volatile (".byte 0x0f, 0x01, 0xd0" : "=a"(lo), "=d"(hi) : "c" (0));
	return lo;
#else
	return 0;
#endif
}