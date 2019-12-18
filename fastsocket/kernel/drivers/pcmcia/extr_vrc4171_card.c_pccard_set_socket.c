#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int io_irq; int csc_irq; } ;
typedef  TYPE_1__ vrc4171_socket_t ;
typedef  int uint8_t ;
struct pcmcia_socket {unsigned int sock; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int Vpp; int Vcc; int flags; scalar_t__ io_irq; int csc_mask; } ;
typedef  TYPE_2__ socket_state_t ;

/* Variables and functions */
 unsigned int CARD_MAX_SLOTS ; 
 int /*<<< orphan*/  CARD_VOLTAGE_SELECT ; 
 int EINVAL ; 
 int /*<<< orphan*/  I365_CSC ; 
 int /*<<< orphan*/  I365_CSCINT ; 
 int I365_CSC_BVD1 ; 
 int I365_CSC_BVD2 ; 
 int I365_CSC_DETECT ; 
 int I365_CSC_READY ; 
 int I365_CSC_STSCHG ; 
 int /*<<< orphan*/  I365_INTCTL ; 
 int I365_PC_IOCARD ; 
 int I365_PC_RESET ; 
 int /*<<< orphan*/  I365_POWER ; 
 int I365_PWR_OUT ; 
 int POWER_ENABLE ; 
 int SS_BATDEAD ; 
 int SS_BATWARN ; 
 int SS_DETECT ; 
 int SS_IOCARD ; 
 int SS_OUTPUT_ENA ; 
 int SS_READY ; 
 int SS_RESET ; 
 int SS_STSCHG ; 
 int VPP_GET_VCC ; 
 int /*<<< orphan*/  exca_read_byte (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_write_byte (unsigned int,int /*<<< orphan*/ ,int) ; 
 int set_Vcc_value (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 TYPE_1__* vrc4171_sockets ; 

__attribute__((used)) static int pccard_set_socket(struct pcmcia_socket *sock, socket_state_t *state)
{
	vrc4171_socket_t *socket;
	unsigned int slot;
	uint8_t voltage, power, control, cscint;

	if (sock == NULL || sock->sock >= CARD_MAX_SLOTS ||
	    (state->Vpp != state->Vcc && state->Vpp != 0) ||
	    (state->Vcc != 50 && state->Vcc != 33 && state->Vcc != 0))
		return -EINVAL;

	slot = sock->sock;
	socket = &vrc4171_sockets[slot];

	spin_lock_irq(&sock->lock);

	voltage = set_Vcc_value(state->Vcc);
	exca_write_byte(slot, CARD_VOLTAGE_SELECT, voltage);

	power = POWER_ENABLE;
	if (state->Vpp == state->Vcc)
		power |= VPP_GET_VCC;
	if (state->flags & SS_OUTPUT_ENA)
		power |= I365_PWR_OUT;
	exca_write_byte(slot, I365_POWER, power);

	control = 0;
	if (state->io_irq != 0)
		control |= socket->io_irq;
	if (state->flags & SS_IOCARD)
		control |= I365_PC_IOCARD;
	if (state->flags & SS_RESET)
		control	&= ~I365_PC_RESET;
	else
		control |= I365_PC_RESET;
	exca_write_byte(slot, I365_INTCTL, control);

        cscint = 0;
        exca_write_byte(slot, I365_CSCINT, cscint);
	exca_read_byte(slot, I365_CSC);	/* clear CardStatus change */
	if (state->csc_mask != 0)
		cscint |= socket->csc_irq << 8;
	if (state->flags & SS_IOCARD) {
		if (state->csc_mask & SS_STSCHG)
			cscint |= I365_CSC_STSCHG;
	} else {
		if (state->csc_mask & SS_BATDEAD)
			cscint |= I365_CSC_BVD1;
		if (state->csc_mask & SS_BATWARN)
			cscint |= I365_CSC_BVD2;
	}
	if (state->csc_mask & SS_READY)
		cscint |= I365_CSC_READY;
	if (state->csc_mask & SS_DETECT)
		cscint |= I365_CSC_DETECT;
        exca_write_byte(slot, I365_CSCINT, cscint);

	spin_unlock_irq(&sock->lock);

	return 0;
}