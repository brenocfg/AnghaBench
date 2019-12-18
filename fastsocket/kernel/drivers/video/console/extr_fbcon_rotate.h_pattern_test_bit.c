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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline int pattern_test_bit(u32 x, u32 y, u32 pitch, const char *pat)
{
	u32 tmp = (y * pitch) + x, index = tmp / 8,  bit = tmp % 8;

	pat +=index;
	return (*pat) & (0x80 >> bit);
}