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
typedef  int uint32_t ;
struct TYPE_2__ {int u; } ;
typedef  TYPE_1__ br_union_u32 ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
br_dec32be(const void *src)
{
#if BR_BE_UNALIGNED
	return ((const br_union_u32 *)src)->u;
#else
	const unsigned char *buf;

	buf = src;
	return ((uint32_t)buf[0] << 24)
		| ((uint32_t)buf[1] << 16)
		| ((uint32_t)buf[2] << 8)
		| (uint32_t)buf[3];
#endif
}