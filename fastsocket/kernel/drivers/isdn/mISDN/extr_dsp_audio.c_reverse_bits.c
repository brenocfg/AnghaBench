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

/* Variables and functions */

__attribute__((used)) static int reverse_bits(int i)
{
	int z, j;
	z = 0;

	for (j = 0; j < 8; j++) {
		if ((i & (1 << j)) != 0)
			z |= 1 << (7 - j);
	}
	return z;
}