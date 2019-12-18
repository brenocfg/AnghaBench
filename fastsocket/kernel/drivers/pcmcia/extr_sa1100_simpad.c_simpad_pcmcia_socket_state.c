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
 unsigned long GPIO_CF_CD ; 
 unsigned long GPIO_CF_IRQ ; 
 unsigned long GPLR ; 
 long get_cs3_shadow () ; 

__attribute__((used)) static void
simpad_pcmcia_socket_state(struct soc_pcmcia_socket *skt,
			   struct pcmcia_state *state)
{
	unsigned long levels = GPLR;
	long cs3reg = get_cs3_shadow();

	state->detect=((levels & GPIO_CF_CD)==0)?1:0;
	state->ready=(levels & GPIO_CF_IRQ)?1:0;
	state->bvd1=1; /* Not available on Simpad. */
	state->bvd2=1; /* Not available on Simpad. */
	state->wrprot=0; /* Not available on Simpad. */
  
	if((cs3reg & 0x0c) == 0x0c) {
		state->vs_3v=0;
		state->vs_Xv=0;
	} else {
		state->vs_3v=1;
		state->vs_Xv=0;
	}
}