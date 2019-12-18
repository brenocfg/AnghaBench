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
struct TYPE_2__ {int u; } ;
typedef  TYPE_1__ br_union_u16 ;

/* Variables and functions */

__attribute__((used)) static inline unsigned
br_dec16be(const void *src)
{
#if BR_BE_UNALIGNED
	return ((const br_union_u16 *)src)->u;
#else
	const unsigned char *buf;

	buf = src;
	return ((unsigned)buf[0] << 8) | (unsigned)buf[1];
#endif
}