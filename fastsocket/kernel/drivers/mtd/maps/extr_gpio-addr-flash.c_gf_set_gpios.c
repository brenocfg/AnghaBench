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
struct async_state {unsigned long win_size; size_t gpio_count; int* gpio_values; int /*<<< orphan*/ * gpio_addrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gf_set_gpios(struct async_state *state, unsigned long ofs)
{
	size_t i = 0;
	int value;
	ofs /= state->win_size;
	do {
		value = ofs & (1 << i);
		if (state->gpio_values[i] != value) {
			gpio_set_value(state->gpio_addrs[i], value);
			state->gpio_values[i] = value;
		}
	} while (++i < state->gpio_count);
}