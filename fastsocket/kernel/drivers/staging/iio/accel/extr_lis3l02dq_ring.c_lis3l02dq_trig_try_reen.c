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
struct lis3l02dq_state {int inter; TYPE_1__* us; } ;
struct iio_trigger {struct lis3l02dq_state* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_gpio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lis3l02dq_trig_try_reen(struct iio_trigger *trig)
{
	struct lis3l02dq_state *st = trig->private_data;
	enable_irq(st->us->irq);
	/* If gpio still high (or high again) */
	if (gpio_get_value(irq_to_gpio(st->us->irq)))
		if (st->inter == 0) {
			/* already interrupt handler dealing with it */
			disable_irq_nosync(st->us->irq);
			if (st->inter == 1) {
				/* interrupt handler snuck in between test
				 * and disable */
				enable_irq(st->us->irq);
				return 0;
			}
			return -EAGAIN;
		}
	/* irq reenabled so success! */
	return 0;
}