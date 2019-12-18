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
struct soc_pcmcia_socket {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EN0 ; 
 int EN1 ; 
 int /*<<< orphan*/  IRQ_GPIO_CF_IRQ ; 
 int VCC_3V_EN ; 
 int VCC_5V_EN ; 
 int /*<<< orphan*/  clear_cs3_bit (int) ; 
 int /*<<< orphan*/  irqs ; 
 int soc_pcmcia_request_irqs (struct soc_pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simpad_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{

	clear_cs3_bit(VCC_3V_EN|VCC_5V_EN|EN0|EN1);

	skt->irq = IRQ_GPIO_CF_IRQ;

	return soc_pcmcia_request_irqs(skt, irqs, ARRAY_SIZE(irqs));
}