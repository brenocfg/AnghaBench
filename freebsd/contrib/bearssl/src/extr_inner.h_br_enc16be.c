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
struct TYPE_2__ {unsigned int u; } ;
typedef  TYPE_1__ br_union_u16 ;

/* Variables and functions */

__attribute__((used)) static inline void
br_enc16be(void *dst, unsigned x)
{
#if BR_BE_UNALIGNED
	((br_union_u16 *)dst)->u = x;
#else
	unsigned char *buf;

	buf = dst;
	buf[0] = (unsigned char)(x >> 8);
	buf[1] = (unsigned char)x;
#endif
}