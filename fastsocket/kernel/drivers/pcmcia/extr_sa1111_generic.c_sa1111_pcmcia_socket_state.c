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
struct soc_pcmcia_socket {int nr; int /*<<< orphan*/  dev; } ;
struct sa1111_dev {scalar_t__ mapbase; } ;
struct pcmcia_state {int detect; int ready; int bvd1; int bvd2; int wrprot; int vs_3v; int vs_Xv; } ;

/* Variables and functions */
 unsigned long PCSR_S0_BVD1 ; 
 unsigned long PCSR_S0_BVD2 ; 
 unsigned long PCSR_S0_DETECT ; 
 unsigned long PCSR_S0_READY ; 
 unsigned long PCSR_S0_VS1 ; 
 unsigned long PCSR_S0_VS2 ; 
 unsigned long PCSR_S0_WP ; 
 unsigned long PCSR_S1_BVD1 ; 
 unsigned long PCSR_S1_BVD2 ; 
 unsigned long PCSR_S1_DETECT ; 
 unsigned long PCSR_S1_READY ; 
 unsigned long PCSR_S1_VS1 ; 
 unsigned long PCSR_S1_VS2 ; 
 unsigned long PCSR_S1_WP ; 
 struct sa1111_dev* SA1111_DEV (int /*<<< orphan*/ ) ; 
 scalar_t__ SA1111_PCSR ; 
 unsigned long sa1111_readl (scalar_t__) ; 

void sa1111_pcmcia_socket_state(struct soc_pcmcia_socket *skt, struct pcmcia_state *state)
{
	struct sa1111_dev *sadev = SA1111_DEV(skt->dev);
	unsigned long status = sa1111_readl(sadev->mapbase + SA1111_PCSR);

	switch (skt->nr) {
	case 0:
		state->detect = status & PCSR_S0_DETECT ? 0 : 1;
		state->ready  = status & PCSR_S0_READY  ? 1 : 0;
		state->bvd1   = status & PCSR_S0_BVD1   ? 1 : 0;
		state->bvd2   = status & PCSR_S0_BVD2   ? 1 : 0;
		state->wrprot = status & PCSR_S0_WP     ? 1 : 0;
		state->vs_3v  = status & PCSR_S0_VS1    ? 0 : 1;
		state->vs_Xv  = status & PCSR_S0_VS2    ? 0 : 1;
		break;

	case 1:
		state->detect = status & PCSR_S1_DETECT ? 0 : 1;
		state->ready  = status & PCSR_S1_READY  ? 1 : 0;
		state->bvd1   = status & PCSR_S1_BVD1   ? 1 : 0;
		state->bvd2   = status & PCSR_S1_BVD2   ? 1 : 0;
		state->wrprot = status & PCSR_S1_WP     ? 1 : 0;
		state->vs_3v  = status & PCSR_S1_VS1    ? 0 : 1;
		state->vs_Xv  = status & PCSR_S1_VS2    ? 0 : 1;
		break;
	}
}