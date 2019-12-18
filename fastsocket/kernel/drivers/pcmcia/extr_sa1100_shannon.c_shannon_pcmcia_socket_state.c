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
struct soc_pcmcia_socket {int nr; } ;
struct pcmcia_state {int detect; int ready; int bvd1; int bvd2; int vs_3v; int /*<<< orphan*/  vs_Xv; int /*<<< orphan*/  wrprot; } ;

/* Variables and functions */
 unsigned long GPLR ; 
 unsigned long SHANNON_GPIO_EJECT_0 ; 
 unsigned long SHANNON_GPIO_EJECT_1 ; 
 unsigned long SHANNON_GPIO_RDY_0 ; 
 unsigned long SHANNON_GPIO_RDY_1 ; 

__attribute__((used)) static void
shannon_pcmcia_socket_state(struct soc_pcmcia_socket *skt,
			    struct pcmcia_state *state)
{
	unsigned long levels = GPLR;

	switch (skt->nr) {
	case 0:
		state->detect = (levels & SHANNON_GPIO_EJECT_0) ? 0 : 1;
		state->ready  = (levels & SHANNON_GPIO_RDY_0) ? 1 : 0;
		state->wrprot = 0; /* Not available on Shannon. */
		state->bvd1   = 1; 
		state->bvd2   = 1; 
		state->vs_3v  = 1; /* FIXME Can only apply 3.3V on Shannon. */
		state->vs_Xv  = 0;
		break;

	case 1:
		state->detect = (levels & SHANNON_GPIO_EJECT_1) ? 0 : 1;
		state->ready  = (levels & SHANNON_GPIO_RDY_1) ? 1 : 0;
		state->wrprot = 0; /* Not available on Shannon. */
		state->bvd1   = 1; 
		state->bvd2   = 1; 
		state->vs_3v  = 1; /* FIXME Can only apply 3.3V on Shannon. */
		state->vs_Xv  = 0;
		break;
	}
}