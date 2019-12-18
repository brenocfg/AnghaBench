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
struct TYPE_2__ {scalar_t__ default_output_value; scalar_t__ pin_usage; scalar_t__ pull_up; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_OUTPUT_LOW ; 
 scalar_t__ DISABLE_PULL_UP ; 
 scalar_t__ GPIO_IN ; 
 int U300_GPIO_MAX ; 
 int U300_GPIO_NUM_PORTS ; 
 int U300_GPIO_PINS_PER_PORT ; 
 int U300_GPIO_PORTX_SPACING ; 
 scalar_t__ U300_GPIO_PXPCR ; 
 int U300_GPIO_PXPCR_PIN_MODE_MASK ; 
 int U300_GPIO_PXPCR_PIN_MODE_OUTPUT_PUSH_PULL ; 
 scalar_t__ U300_GPIO_PXPDOR ; 
 scalar_t__ U300_GPIO_PXPER ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int readl (scalar_t__) ; 
 TYPE_1__** u300_gpio_config ; 
 scalar_t__ virtbase ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gpio_set_initial_values(void)
{
#ifdef U300_COH901571_3
	int i, j;
	unsigned long flags;
	u32 val;

	/* Write default values to all pins */
	for (i = 0; i < U300_GPIO_NUM_PORTS; i++) {
		val = 0;
		for (j = 0; j < 8; j++)
			val |= (u32) (u300_gpio_config[i][j].default_output_value != DEFAULT_OUTPUT_LOW) << j;
		local_irq_save(flags);
		writel(val, virtbase + U300_GPIO_PXPDOR + i * U300_GPIO_PORTX_SPACING);
		local_irq_restore(flags);
	}

	/*
	 * Put all pins that are set to either 'GPIO_OUT' or 'GPIO_NOT_USED'
	 * to output and 'GPIO_IN' to input for each port. And initalize
	 * default value on outputs.
	 */
	for (i = 0; i < U300_GPIO_NUM_PORTS; i++) {
		for (j = 0; j < U300_GPIO_PINS_PER_PORT; j++) {
			local_irq_save(flags);
			val = readl(virtbase + U300_GPIO_PXPCR +
					 i * U300_GPIO_PORTX_SPACING);
			/* Mask out this pin */
			val &= ~(U300_GPIO_PXPCR_PIN_MODE_MASK << (j << 1));

			if (u300_gpio_config[i][j].pin_usage != GPIO_IN)
				val |= (U300_GPIO_PXPCR_PIN_MODE_OUTPUT_PUSH_PULL << (j << 1));
			writel(val, virtbase + U300_GPIO_PXPCR +
					 i * U300_GPIO_PORTX_SPACING);
			local_irq_restore(flags);
		}
	}

	/* Enable or disable the internal pull-ups in the GPIO ASIC block */
	for (i = 0; i < U300_GPIO_MAX; i++) {
		val = 0;
		for (j = 0; j < 8; j++)
			val |= (u32)((u300_gpio_config[i][j].pull_up == DISABLE_PULL_UP)) << j;
		local_irq_save(flags);
		writel(val, virtbase + U300_GPIO_PXPER + i * U300_GPIO_PORTX_SPACING);
		local_irq_restore(flags);
	}
#endif
}