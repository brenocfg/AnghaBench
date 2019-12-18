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
struct input_dev {int dummy; } ;
struct ep93xx_keypad {int enabled; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_keypad_config (struct ep93xx_keypad*) ; 
 struct ep93xx_keypad* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int ep93xx_keypad_open(struct input_dev *pdev)
{
	struct ep93xx_keypad *keypad = input_get_drvdata(pdev);

	if (!keypad->enabled) {
		ep93xx_keypad_config(keypad);
		clk_enable(keypad->clk);
		keypad->enabled = 1;
	}

	return 0;
}