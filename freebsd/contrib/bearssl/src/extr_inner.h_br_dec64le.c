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
typedef  int uint64_t ;
struct TYPE_2__ {int u; } ;
typedef  TYPE_1__ br_union_u64 ;

/* Variables and functions */
 scalar_t__ br_dec32le (unsigned char const*) ; 

__attribute__((used)) static inline uint64_t
br_dec64le(const void *src)
{
#if BR_LE_UNALIGNED
	return ((const br_union_u64 *)src)->u;
#else
	const unsigned char *buf;

	buf = src;
	return (uint64_t)br_dec32le(buf)
		| ((uint64_t)br_dec32le(buf + 4) << 32);
#endif
}