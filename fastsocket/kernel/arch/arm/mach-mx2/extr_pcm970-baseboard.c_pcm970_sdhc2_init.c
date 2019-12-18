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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 scalar_t__ GPIO_PORTC ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  IRQ_GPIOC (int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gpio_direction_input (scalar_t__) ; 
 int gpio_request (scalar_t__,char*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int pcm970_sdhc2_init(struct device *dev, irq_handler_t detect_irq, void *data)
{
	int ret;

	ret = request_irq(IRQ_GPIOC(29), detect_irq, IRQF_TRIGGER_FALLING,
				"imx-mmc-detect", data);
	if (ret)
		return ret;

	ret = gpio_request(GPIO_PORTC + 28, "imx-mmc-ro");
	if (ret) {
		free_irq(IRQ_GPIOC(29), data);
		return ret;
	}

	gpio_direction_input(GPIO_PORTC + 28);

	return 0;
}