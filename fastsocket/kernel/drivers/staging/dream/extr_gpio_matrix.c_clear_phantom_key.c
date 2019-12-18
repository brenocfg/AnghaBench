#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_kp {int /*<<< orphan*/  keys_pressed; TYPE_1__* input_dev; struct gpio_event_matrix_info* keypad_info; } ;
struct gpio_event_matrix_info {int ninputs; unsigned short* keymap; int flags; int /*<<< orphan*/ * input_gpios; int /*<<< orphan*/ * output_gpios; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int GPIOKPF_PRINT_PHANTOM_KEYS ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned short,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_phantom_key(struct gpio_kp *kp, int out, int in)
{
	struct gpio_event_matrix_info *mi = kp->keypad_info;
	int key_index = out * mi->ninputs + in;
	unsigned short keycode = mi->keymap[key_index];;

	if (!test_bit(keycode, kp->input_dev->key)) {
		if (mi->flags & GPIOKPF_PRINT_PHANTOM_KEYS)
			pr_info("gpiomatrix: phantom key %x, %d-%d (%d-%d) "
				"cleared\n", keycode, out, in,
				mi->output_gpios[out], mi->input_gpios[in]);
		__clear_bit(key_index, kp->keys_pressed);
	} else {
		if (mi->flags & GPIOKPF_PRINT_PHANTOM_KEYS)
			pr_info("gpiomatrix: phantom key %x, %d-%d (%d-%d) "
				"not cleared\n", keycode, out, in,
				mi->output_gpios[out], mi->input_gpios[in]);
	}
}