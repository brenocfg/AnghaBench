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
struct TYPE_2__ {scalar_t__ pressure; } ;
struct corgi_ts {int pendown; int /*<<< orphan*/  irq_gpio; TYPE_1__ tc; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int GPIO_bit (int /*<<< orphan*/ ) ; 
 int GPLR (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  IRQ_TO_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_FALLING ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  new_data (struct corgi_ts*) ; 
 scalar_t__ read_xydata (struct corgi_ts*) ; 
 int /*<<< orphan*/  set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ts_interrupt_main(struct corgi_ts *corgi_ts, int isTimer)
{
	if ((GPLR(IRQ_TO_GPIO(corgi_ts->irq_gpio)) & GPIO_bit(IRQ_TO_GPIO(corgi_ts->irq_gpio))) == 0) {
		/* Disable Interrupt */
		set_irq_type(corgi_ts->irq_gpio, IRQ_TYPE_NONE);
		if (read_xydata(corgi_ts)) {
			corgi_ts->pendown = 1;
			new_data(corgi_ts);
		}
		mod_timer(&corgi_ts->timer, jiffies + HZ / 100);
	} else {
		if (corgi_ts->pendown == 1 || corgi_ts->pendown == 2) {
			mod_timer(&corgi_ts->timer, jiffies + HZ / 100);
			corgi_ts->pendown++;
			return;
		}

		if (corgi_ts->pendown) {
			corgi_ts->tc.pressure = 0;
			new_data(corgi_ts);
		}

		/* Enable Falling Edge */
		set_irq_type(corgi_ts->irq_gpio, IRQ_TYPE_EDGE_FALLING);
		corgi_ts->pendown = 0;
	}
}