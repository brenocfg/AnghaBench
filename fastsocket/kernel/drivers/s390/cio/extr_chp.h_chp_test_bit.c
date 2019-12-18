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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline int chp_test_bit(u8 *bitmap, int num)
{
	int byte = num >> 3;
	int mask = 128 >> (num & 7);

	return (bitmap[byte] & mask) ? 1 : 0;
}