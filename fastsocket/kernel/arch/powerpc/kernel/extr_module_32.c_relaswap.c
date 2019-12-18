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
typedef  int /*<<< orphan*/  Elf32_Rela ;

/* Variables and functions */

__attribute__((used)) static void relaswap(void *_x, void *_y, int size)
{
	uint32_t *x, *y, tmp;
	int i;

	y = (uint32_t *)_x;
	x = (uint32_t *)_y;

	for (i = 0; i < sizeof(Elf32_Rela) / sizeof(uint32_t); i++) {
		tmp = x[i];
		x[i] = y[i];
		y[i] = tmp;
	}
}