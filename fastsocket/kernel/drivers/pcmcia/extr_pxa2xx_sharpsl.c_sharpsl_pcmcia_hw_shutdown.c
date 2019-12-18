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
struct soc_pcmcia_socket {size_t nr; } ;
struct pcmcia_irqs {size_t sock; scalar_t__ irq; int /*<<< orphan*/  str; } ;
struct TYPE_2__ {scalar_t__ cd_irq; int /*<<< orphan*/  cd_irq_str; } ;

/* Variables and functions */
 TYPE_1__* SCOOP_DEV ; 
 int /*<<< orphan*/  soc_pcmcia_free_irqs (struct soc_pcmcia_socket*,struct pcmcia_irqs*,int) ; 

__attribute__((used)) static void sharpsl_pcmcia_hw_shutdown(struct soc_pcmcia_socket *skt)
{
	if (SCOOP_DEV[skt->nr].cd_irq >= 0) {
		struct pcmcia_irqs cd_irq;

		cd_irq.sock = skt->nr;
		cd_irq.irq  = SCOOP_DEV[skt->nr].cd_irq;
		cd_irq.str  = SCOOP_DEV[skt->nr].cd_irq_str;
		soc_pcmcia_free_irqs(skt, &cd_irq, 1);
	}
}