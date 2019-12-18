#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct soc_pcmcia_socket {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GPIO_PRDY ; 
 int /*<<< orphan*/  IRQ_TO_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* irqs ; 

__attribute__((used)) static void trizeps_pcmcia_hw_shutdown(struct soc_pcmcia_socket *skt)
{
	int i;
	/* free allocated gpio's */
	gpio_free(GPIO_PRDY);
	for (i = 0; i < ARRAY_SIZE(irqs); i++)
		gpio_free(IRQ_TO_GPIO(irqs[i].irq));
}