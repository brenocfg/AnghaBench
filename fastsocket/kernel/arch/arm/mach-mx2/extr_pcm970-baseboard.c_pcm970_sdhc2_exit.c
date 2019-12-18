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

/* Variables and functions */
 scalar_t__ GPIO_PORTC ; 
 int /*<<< orphan*/  IRQ_GPIOC (int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 

__attribute__((used)) static void pcm970_sdhc2_exit(struct device *dev, void *data)
{
	free_irq(IRQ_GPIOC(29), data);
	gpio_free(GPIO_PORTC + 28);
}