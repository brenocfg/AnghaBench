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
typedef  size_t u16 ;
struct input_dev {size_t keycodemax; } ;
struct bf54x_kpad {size_t* keycode; } ;

/* Variables and functions */

__attribute__((used)) static inline int bfin_kpad_find_key(struct bf54x_kpad *bf54x_kpad,
			struct input_dev *input, u16 keyident)
{
	u16 i;

	for (i = 0; i < input->keycodemax; i++)
		if (bf54x_kpad->keycode[i + input->keycodemax] == keyident)
			return bf54x_kpad->keycode[i];
	return -1;
}