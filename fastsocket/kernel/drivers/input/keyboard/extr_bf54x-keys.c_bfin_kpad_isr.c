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
typedef  int /*<<< orphan*/  u16 ;
struct platform_device {int dummy; } ;
struct input_dev {int dummy; } ;
struct bf54x_kpad {int lastkey; scalar_t__ keyup_test_jiffies; int /*<<< orphan*/  timer; int /*<<< orphan*/  irq; struct input_dev* input; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bfin_kpad_clear_irq () ; 
 int bfin_kpad_find_key (struct bf54x_kpad*,struct input_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ bfin_kpad_get_keypressed (struct bf54x_kpad*) ; 
 int /*<<< orphan*/  bfin_read_KPAD_ROWCOL () ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct bf54x_kpad* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static irqreturn_t bfin_kpad_isr(int irq, void *dev_id)
{
	struct platform_device *pdev = dev_id;
	struct bf54x_kpad *bf54x_kpad = platform_get_drvdata(pdev);
	struct input_dev *input = bf54x_kpad->input;
	int key;
	u16 rowcol = bfin_read_KPAD_ROWCOL();

	key = bfin_kpad_find_key(bf54x_kpad, input, rowcol);

	input_report_key(input, key, 1);
	input_sync(input);

	if (bfin_kpad_get_keypressed(bf54x_kpad)) {
		disable_irq(bf54x_kpad->irq);
		bf54x_kpad->lastkey = key;
		mod_timer(&bf54x_kpad->timer,
			  jiffies + bf54x_kpad->keyup_test_jiffies);
	} else {
		input_report_key(input, key, 0);
		input_sync(input);

		bfin_kpad_clear_irq();
	}

	return IRQ_HANDLED;
}