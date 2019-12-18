#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int Word_t ;
struct TYPE_8__ {unsigned int numPorts; } ;
struct TYPE_7__ {scalar_t__ BusType; unsigned int* AiopIntrBits; } ;
typedef  TYPE_1__ CONTROLLER_t ;

/* Variables and functions */
 int GetLineNumber (int,int,int) ; 
 scalar_t__ POLL_PERIOD ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ isPCI ; 
 scalar_t__ jiffies ; 
 int max_board ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__* rcktpt_io_addr ; 
 TYPE_6__* rocketModel ; 
 int /*<<< orphan*/  rocket_timer ; 
 int /*<<< orphan*/  rp_do_transmit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp_handle_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp_num_ports_open ; 
 int /*<<< orphan*/ * rp_table ; 
 TYPE_1__* sCtlNumToCtlPtr (int) ; 
 unsigned char sGetAiopIntStatus (TYPE_1__*,int) ; 
 unsigned int sGetControllerIntStatus (TYPE_1__*) ; 
 unsigned int sPCIGetControllerIntStatus (TYPE_1__*) ; 
 unsigned int* xmit_flags ; 

__attribute__((used)) static void rp_do_poll(unsigned long dummy)
{
	CONTROLLER_t *ctlp;
	int ctrl, aiop, ch, line;
	unsigned int xmitmask, i;
	unsigned int CtlMask;
	unsigned char AiopMask;
	Word_t bit;

	/*  Walk through all the boards (ctrl's) */
	for (ctrl = 0; ctrl < max_board; ctrl++) {
		if (rcktpt_io_addr[ctrl] <= 0)
			continue;

		/*  Get a ptr to the board's control struct */
		ctlp = sCtlNumToCtlPtr(ctrl);

		/*  Get the interrupt status from the board */
#ifdef CONFIG_PCI
		if (ctlp->BusType == isPCI)
			CtlMask = sPCIGetControllerIntStatus(ctlp);
		else
#endif
			CtlMask = sGetControllerIntStatus(ctlp);

		/*  Check if any AIOP read bits are set */
		for (aiop = 0; CtlMask; aiop++) {
			bit = ctlp->AiopIntrBits[aiop];
			if (CtlMask & bit) {
				CtlMask &= ~bit;
				AiopMask = sGetAiopIntStatus(ctlp, aiop);

				/*  Check if any port read bits are set */
				for (ch = 0; AiopMask;  AiopMask >>= 1, ch++) {
					if (AiopMask & 1) {

						/*  Get the line number (/dev/ttyRx number). */
						/*  Read the data from the port. */
						line = GetLineNumber(ctrl, aiop, ch);
						rp_handle_port(rp_table[line]);
					}
				}
			}
		}

		xmitmask = xmit_flags[ctrl];

		/*
		 *  xmit_flags contains bit-significant flags, indicating there is data
		 *  to xmit on the port. Bit 0 is port 0 on this board, bit 1 is port 
		 *  1, ... (32 total possible).  The variable i has the aiop and ch 
		 *  numbers encoded in it (port 0-7 are aiop0, 8-15 are aiop1, etc).
		 */
		if (xmitmask) {
			for (i = 0; i < rocketModel[ctrl].numPorts; i++) {
				if (xmitmask & (1 << i)) {
					aiop = (i & 0x18) >> 3;
					ch = i & 0x07;
					line = GetLineNumber(ctrl, aiop, ch);
					rp_do_transmit(rp_table[line]);
				}
			}
		}
	}

	/*
	 * Reset the timer so we get called at the next clock tick (10ms).
	 */
	if (atomic_read(&rp_num_ports_open))
		mod_timer(&rocket_timer, jiffies + POLL_PERIOD);
}