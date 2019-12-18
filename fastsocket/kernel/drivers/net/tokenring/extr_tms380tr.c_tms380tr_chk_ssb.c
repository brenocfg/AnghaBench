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
struct TYPE_2__ {unsigned short STS; unsigned short* Parm; } ;
struct net_local {TYPE_1__ ssb; } ;
typedef  TYPE_1__ SSB ;

/* Variables and functions */
 unsigned short STS_IRQ_COMMAND_STATUS ; 
 unsigned short STS_IRQ_RECEIVE_STATUS ; 
 unsigned short STS_IRQ_RING_STATUS ; 
 unsigned short STS_IRQ_TRANSMIT_STATUS ; 

__attribute__((used)) static unsigned char tms380tr_chk_ssb(struct net_local *tp, unsigned short IrqType)
{
	SSB *ssb = &tp->ssb;	/* The address of the SSB. */

	/* C 0 1 2 INTERRUPT CODE
	 * - - - - --------------
	 * 1 1 1 1 TRANSMIT STATUS
	 * 1 1 1 1 RECEIVE STATUS
	 * 1 ? ? 0 COMMAND STATUS
	 * 0 0 0 0 SCB CLEAR
	 * 1 1 0 0 RING STATUS
	 * 0 0 0 0 ADAPTER CHECK
	 *
	 * 0 = SSB field not affected by interrupt
	 * 1 = SSB field is affected by interrupt
	 *
	 * C = SSB ADDRESS +0: COMMAND
	 * 0 = SSB ADDRESS +2: STATUS 0
	 * 1 = SSB ADDRESS +4: STATUS 1
	 * 2 = SSB ADDRESS +6: STATUS 2
	 */

	/* Check if this interrupt does use the SSB. */

	if(IrqType != STS_IRQ_TRANSMIT_STATUS
		&& IrqType != STS_IRQ_RECEIVE_STATUS
		&& IrqType != STS_IRQ_COMMAND_STATUS
		&& IrqType != STS_IRQ_RING_STATUS)
	{
		return (1);	/* SSB not involved. */
	}

	/* Note: All fields of the SSB have been set to all ones (-1) after it
	 * has last been used by the software (see DriverIsr()).
	 *
	 * Check if the affected SSB fields are still unchanged.
	 */

	if(ssb->STS == (unsigned short) -1)
		return (0);	/* Command field not yet available. */
	if(IrqType == STS_IRQ_COMMAND_STATUS)
		return (1);	/* Status fields not always affected. */
	if(ssb->Parm[0] == (unsigned short) -1)
		return (0);	/* Status 1 field not yet available. */
	if(IrqType == STS_IRQ_RING_STATUS)
		return (1);	/* Status 2 & 3 fields not affected. */

	/* Note: At this point, the interrupt is either TRANSMIT or RECEIVE. */
	if(ssb->Parm[1] == (unsigned short) -1)
		return (0);	/* Status 2 field not yet available. */
	if(ssb->Parm[2] == (unsigned short) -1)
		return (0);	/* Status 3 field not yet available. */

	return (1);	/* All SSB fields have been written by the adapter. */
}