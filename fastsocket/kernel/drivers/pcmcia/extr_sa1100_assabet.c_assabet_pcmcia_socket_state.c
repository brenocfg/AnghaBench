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
struct pcmcia_state {int detect; int ready; int bvd1; int bvd2; int vs_3v; scalar_t__ vs_Xv; scalar_t__ wrprot; } ;

/* Variables and functions */
 unsigned long ASSABET_GPIO_CF_BVD1 ; 
 unsigned long ASSABET_GPIO_CF_BVD2 ; 
 unsigned long ASSABET_GPIO_CF_CD ; 
 unsigned long ASSABET_GPIO_CF_IRQ ; 
 unsigned long GPLR ; 

__attribute__((used)) static void
assabet_pcmcia_socket_state(struct soc_pcmcia_socket *skt, struct pcmcia_state *state)
{
	unsigned long levels = GPLR;

	state->detect = (levels & ASSABET_GPIO_CF_CD) ? 0 : 1;
	state->ready  = (levels & ASSABET_GPIO_CF_IRQ) ? 1 : 0;
	state->bvd1   = (levels & ASSABET_GPIO_CF_BVD1) ? 1 : 0;
	state->bvd2   = (levels & ASSABET_GPIO_CF_BVD2) ? 1 : 0;
	state->wrprot = 0; /* Not available on Assabet. */
	state->vs_3v  = 1; /* Can only apply 3.3V on Assabet. */
	state->vs_Xv  = 0;
}