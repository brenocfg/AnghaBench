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
typedef  int u32 ;
struct u300_gpio_port {int number; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int U300_GPIO_PORTX_SPACING ; 
 scalar_t__ U300_GPIO_PXIEV ; 
 int U300_GPIO_PXIEV_ALL_IRQ_EVENT_MASK ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 TYPE_1__* gpio_pin ; 
 int /*<<< orphan*/  gpiodev ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ virtbase ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t gpio_irq_handler(int irq, void *dev_id)
{
	struct u300_gpio_port *port = dev_id;
	u32 val;
	int pin;

	/* Read event register */
	val = readl(virtbase + U300_GPIO_PXIEV + port->number *
				U300_GPIO_PORTX_SPACING);
	/* Mask with enable register */
	val &= readl(virtbase + U300_GPIO_PXIEV + port->number *
				U300_GPIO_PORTX_SPACING);
	/* Mask relevant bits */
	val &= U300_GPIO_PXIEV_ALL_IRQ_EVENT_MASK;
	/* ACK IRQ (clear event) */
	writel(val, virtbase + U300_GPIO_PXIEV + port->number *
				U300_GPIO_PORTX_SPACING);
	/* Print message */
	while (val != 0) {
		unsigned gpio;

		pin = __ffs(val);
		/* mask off this pin */
		val &= ~(1 << pin);
		gpio = (port->number << 3) + pin;

		if (gpio_pin[gpio].callback)
			(void)gpio_pin[gpio].callback(gpio_pin[gpio].data);
		else
			dev_dbg(gpiodev, "stray GPIO IRQ on line %d\n",
			       gpio);
	}
	return IRQ_HANDLED;
}