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
struct pcmcia_irq_info {scalar_t__ sock; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCMCIA_IRQ ; 
 scalar_t__ PCMCIA_MAX_SOCK ; 

__attribute__((used)) static int pb1x00_pcmcia_get_irq_info(struct pcmcia_irq_info *info)
{

	if(info->sock > PCMCIA_MAX_SOCK) return -1;

	/*
	 * Even in the case of the Pb1000, both sockets are connected
	 * to the same irq line.
	 */
	info->irq = PCMCIA_IRQ;

	return 0;
}