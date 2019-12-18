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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct matrix_keypad {int stopped; TYPE_1__ work; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_row_irqs (struct matrix_keypad*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct matrix_keypad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void matrix_keypad_stop(struct input_dev *dev)
{
	struct matrix_keypad *keypad = input_get_drvdata(dev);

	keypad->stopped = true;
	mb();
	flush_work(&keypad->work.work);
	/*
	 * matrix_keypad_scan() will leave IRQs enabled;
	 * we should disable them now.
	 */
	disable_row_irqs(keypad);
}