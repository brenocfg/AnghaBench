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
struct soc_pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCMCIA_RESET ; 
 int /*<<< orphan*/  clear_cs3_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs ; 
 int /*<<< orphan*/  soc_pcmcia_free_irqs (struct soc_pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void simpad_pcmcia_hw_shutdown(struct soc_pcmcia_socket *skt)
{
	soc_pcmcia_free_irqs(skt, irqs, ARRAY_SIZE(irqs));

	/* Disable CF bus: */
	//set_cs3_bit(PCMCIA_BUFF_DIS);
	clear_cs3_bit(PCMCIA_RESET);       
}