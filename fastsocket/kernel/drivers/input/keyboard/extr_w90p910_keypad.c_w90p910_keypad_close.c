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
struct w90p910_keypad {int /*<<< orphan*/  clk; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct w90p910_keypad* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void w90p910_keypad_close(struct input_dev *dev)
{
	struct w90p910_keypad *keypad = input_get_drvdata(dev);

	/* Disable clock unit */
	clk_disable(keypad->clk);
}