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
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int DB0_GPIO_PIN ; 
 int DB15_GPIO_PIN ; 
 int /*<<< orphan*/  IRQ_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDY_GPIO_PIN ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct broadsheetfb_par*) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int* gpios ; 

__attribute__((used)) static void am300_cleanup(struct broadsheetfb_par *par)
{
	int i;

	free_irq(IRQ_GPIO(RDY_GPIO_PIN), par);

	for (i = 0; i < ARRAY_SIZE(gpios); i++)
		gpio_free(gpios[i]);

	for (i = DB0_GPIO_PIN; i <= DB15_GPIO_PIN; i++)
		gpio_free(i);

}