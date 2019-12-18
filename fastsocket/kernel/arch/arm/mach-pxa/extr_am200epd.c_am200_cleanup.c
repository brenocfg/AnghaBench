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
struct metronomefb_par {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQ_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDY_GPIO_PIN ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct metronomefb_par*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gpios ; 

__attribute__((used)) static void am200_cleanup(struct metronomefb_par *par)
{
	int i;

	free_irq(IRQ_GPIO(RDY_GPIO_PIN), par);

	for (i = 0; i < ARRAY_SIZE(gpios); i++)
		gpio_free(gpios[i]);
}