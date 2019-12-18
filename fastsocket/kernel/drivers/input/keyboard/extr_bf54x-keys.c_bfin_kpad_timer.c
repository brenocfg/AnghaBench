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
struct platform_device {int dummy; } ;
struct bf54x_kpad {int /*<<< orphan*/  irq; int /*<<< orphan*/  input; int /*<<< orphan*/  lastkey; scalar_t__ keyup_test_jiffies; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfin_kpad_clear_irq () ; 
 scalar_t__ bfin_kpad_get_keypressed (struct bf54x_kpad*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct bf54x_kpad* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void bfin_kpad_timer(unsigned long data)
{
	struct platform_device *pdev =  (struct platform_device *) data;
	struct bf54x_kpad *bf54x_kpad = platform_get_drvdata(pdev);

	if (bfin_kpad_get_keypressed(bf54x_kpad)) {
		/* Try again later */
		mod_timer(&bf54x_kpad->timer,
			  jiffies + bf54x_kpad->keyup_test_jiffies);
		return;
	}

	input_report_key(bf54x_kpad->input, bf54x_kpad->lastkey, 0);
	input_sync(bf54x_kpad->input);

	/* Clear IRQ Status */

	bfin_kpad_clear_irq();
	enable_irq(bf54x_kpad->irq);
}