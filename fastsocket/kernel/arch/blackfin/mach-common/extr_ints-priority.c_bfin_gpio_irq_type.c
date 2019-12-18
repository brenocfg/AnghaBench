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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_PROBE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_gpio_irq_prepare (int /*<<< orphan*/ ) ; 
 int bfin_gpio_irq_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfin_set_irq_handler (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_enabled ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_to_gpio (unsigned int) ; 
 int /*<<< orphan*/  set_gpio_both (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_gpio_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_edge (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_gpio_inen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_gpio_polar (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfin_gpio_irq_type(unsigned int irq, unsigned int type)
{
	int ret;
	char buf[16];
	u32 gpionr = irq_to_gpio(irq);

	if (type == IRQ_TYPE_PROBE) {
		/* only probe unenabled GPIO interrupt lines */
		if (test_bit(gpionr, gpio_enabled))
			return 0;
		type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	}

	if (type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING |
		    IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) {

		snprintf(buf, 16, "gpio-irq%d", irq);
		ret = bfin_gpio_irq_request(gpionr, buf);
		if (ret)
			return ret;

		if (__test_and_set_bit(gpionr, gpio_enabled))
			bfin_gpio_irq_prepare(gpionr);

	} else {
		__clear_bit(gpionr, gpio_enabled);
		return 0;
	}

	set_gpio_inen(gpionr, 0);
	set_gpio_dir(gpionr, 0);

	if ((type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING))
	    == (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING))
		set_gpio_both(gpionr, 1);
	else
		set_gpio_both(gpionr, 0);

	if ((type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_LEVEL_LOW)))
		set_gpio_polar(gpionr, 1);	/* low or falling edge denoted by one */
	else
		set_gpio_polar(gpionr, 0);	/* high or rising edge denoted by zero */

	if (type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING)) {
		set_gpio_edge(gpionr, 1);
		set_gpio_inen(gpionr, 1);
		set_gpio_data(gpionr, 0);

	} else {
		set_gpio_edge(gpionr, 0);
		set_gpio_inen(gpionr, 1);
	}

	if (type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING))
		bfin_set_irq_handler(irq, handle_edge_irq);
	else
		bfin_set_irq_handler(irq, handle_level_irq);

	return 0;
}