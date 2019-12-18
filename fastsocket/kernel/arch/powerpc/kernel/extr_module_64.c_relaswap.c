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
typedef  int /*<<< orphan*/  Elf64_Rela ;

/* Variables and functions */

__attribute__((used)) static void relaswap(void *_x, void *_y, int size)
{
	uint64_t *x, *y, tmp;
	int i;

	y = (uint64_t *)_x;
	x = (uint64_t *)_y;

	for (i = 0; i < sizeof(Elf64_Rela) / sizeof(uint64_t); i++) {
		tmp = x[i];
		x[i] = y[i];
		y[i] = tmp;
	}
}