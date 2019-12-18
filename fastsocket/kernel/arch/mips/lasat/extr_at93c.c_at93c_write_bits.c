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
 int /*<<< orphan*/  at93c_write_databit (int) ; 

__attribute__((used)) static void at93c_write_bits(u32 data, int size)
{
	int i;
	int shift = size - 1;
	u32 mask = (1 << shift);

	for (i = 0; i < size; i++) {
		at93c_write_databit((data & mask) >> shift);
		data <<= 1;
	}
}