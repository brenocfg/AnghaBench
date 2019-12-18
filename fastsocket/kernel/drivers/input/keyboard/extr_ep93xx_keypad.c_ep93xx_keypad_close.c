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
struct ep93xx_keypad {scalar_t__ enabled; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct ep93xx_keypad* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void ep93xx_keypad_close(struct input_dev *pdev)
{
	struct ep93xx_keypad *keypad = input_get_drvdata(pdev);

	if (keypad->enabled) {
		clk_disable(keypad->clk);
		keypad->enabled = 0;
	}
}