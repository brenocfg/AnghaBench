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
 int /*<<< orphan*/  GPIO_PCMCIA_RESET ; 
 int /*<<< orphan*/  PCMCIA_S0_RDYINT ; 
 int /*<<< orphan*/  PCMCIA_S1_RDYINT ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  irqs ; 
 int soc_pcmcia_request_irqs (struct soc_pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmx255_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	int ret = gpio_request(GPIO_PCMCIA_RESET, "PCCard reset");
	if (ret)
		return ret;
	gpio_direction_output(GPIO_PCMCIA_RESET, 0);

	skt->irq = skt->nr == 0 ? PCMCIA_S0_RDYINT : PCMCIA_S1_RDYINT;
	ret = soc_pcmcia_request_irqs(skt, irqs, ARRAY_SIZE(irqs));
	if (!ret)
		gpio_free(GPIO_PCMCIA_RESET);

	return ret;
}