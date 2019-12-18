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
struct soc_pcmcia_socket {scalar_t__ nr; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int GAFR ; 
 int GPDR ; 
 int SHANNON_GPIO_EJECT_0 ; 
 int SHANNON_GPIO_EJECT_1 ; 
 int SHANNON_GPIO_RDY_0 ; 
 int SHANNON_GPIO_RDY_1 ; 
 int /*<<< orphan*/  SHANNON_IRQ_GPIO_RDY_0 ; 
 int /*<<< orphan*/  SHANNON_IRQ_GPIO_RDY_1 ; 
 int /*<<< orphan*/  irqs ; 
 int soc_pcmcia_request_irqs (struct soc_pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shannon_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	/* All those are inputs */
	GPDR &= ~(SHANNON_GPIO_EJECT_0 | SHANNON_GPIO_EJECT_1 | 
		  SHANNON_GPIO_RDY_0 | SHANNON_GPIO_RDY_1);
	GAFR &= ~(SHANNON_GPIO_EJECT_0 | SHANNON_GPIO_EJECT_1 | 
		  SHANNON_GPIO_RDY_0 | SHANNON_GPIO_RDY_1);

	skt->irq = skt->nr ? SHANNON_IRQ_GPIO_RDY_1 : SHANNON_IRQ_GPIO_RDY_0;

	return soc_pcmcia_request_irqs(skt, irqs, ARRAY_SIZE(irqs));
}