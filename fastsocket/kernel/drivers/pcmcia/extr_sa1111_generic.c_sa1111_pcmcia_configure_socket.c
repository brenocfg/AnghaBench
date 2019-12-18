#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct soc_pcmcia_socket {int nr; int /*<<< orphan*/  dev; } ;
struct sa1111_dev {scalar_t__ mapbase; } ;
struct TYPE_3__ {int Vcc; int flags; } ;
typedef  TYPE_1__ socket_state_t ;

/* Variables and functions */
 unsigned int PCCR_S0_FLT ; 
 unsigned int PCCR_S0_PSE ; 
 unsigned int PCCR_S0_PWAITEN ; 
 unsigned int PCCR_S0_RST ; 
 unsigned int PCCR_S1_FLT ; 
 unsigned int PCCR_S1_PSE ; 
 unsigned int PCCR_S1_PWAITEN ; 
 unsigned int PCCR_S1_RST ; 
 struct sa1111_dev* SA1111_DEV (int /*<<< orphan*/ ) ; 
 scalar_t__ SA1111_PCCR ; 
 int SS_OUTPUT_ENA ; 
 int SS_RESET ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned int sa1111_readl (scalar_t__) ; 
 int /*<<< orphan*/  sa1111_writel (unsigned int,scalar_t__) ; 

int sa1111_pcmcia_configure_socket(struct soc_pcmcia_socket *skt, const socket_state_t *state)
{
	struct sa1111_dev *sadev = SA1111_DEV(skt->dev);
	unsigned int pccr_skt_mask, pccr_set_mask, val;
	unsigned long flags;

	switch (skt->nr) {
	case 0:
		pccr_skt_mask = PCCR_S0_RST|PCCR_S0_FLT|PCCR_S0_PWAITEN|PCCR_S0_PSE;
		break;

	case 1:
		pccr_skt_mask = PCCR_S1_RST|PCCR_S1_FLT|PCCR_S1_PWAITEN|PCCR_S1_PSE;
		break;

	default:
		return -1;
	}

	pccr_set_mask = 0;

	if (state->Vcc != 0)
		pccr_set_mask |= PCCR_S0_PWAITEN|PCCR_S1_PWAITEN;
	if (state->Vcc == 50)
		pccr_set_mask |= PCCR_S0_PSE|PCCR_S1_PSE;
	if (state->flags & SS_RESET)
		pccr_set_mask |= PCCR_S0_RST|PCCR_S1_RST;
	if (state->flags & SS_OUTPUT_ENA)
		pccr_set_mask |= PCCR_S0_FLT|PCCR_S1_FLT;

	local_irq_save(flags);
	val = sa1111_readl(sadev->mapbase + SA1111_PCCR);
	val &= ~pccr_skt_mask;
	val |= pccr_set_mask & pccr_skt_mask;
	sa1111_writel(val, sadev->mapbase + SA1111_PCCR);
	local_irq_restore(flags);

	return 0;
}