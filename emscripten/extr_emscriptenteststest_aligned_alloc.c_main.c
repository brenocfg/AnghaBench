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
 scalar_t__ aligned_alloc (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 

int main()
{
	for(int times = 0; times < 16; ++times)
		for(int alignment = sizeof(void*); alignment <= 64; alignment *= 2)
			assert((uintptr_t)aligned_alloc(alignment, 19) % alignment == 0);
	return 0;
}