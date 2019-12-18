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
typedef  int /*<<< orphan*/  diff ;

/* Variables and functions */
 int in_gp2x_get_bits () ; 

int in_gp2x_update_keycode(void *data, int *is_down)
{
	static int old_val = 0;
	int val, diff, i;

	val = in_gp2x_get_bits();
	diff = val ^ old_val;
	if (diff == 0)
		return -1;

	/* take one bit only */
	for (i = 0; i < sizeof(diff)*8; i++)
		if (diff & (1<<i))
			break;

	old_val ^= 1 << i;

	if (is_down)
		*is_down = !!(val & (1<<i));
	return i;
}