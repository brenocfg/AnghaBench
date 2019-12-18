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
struct TYPE_2__ {int /*<<< orphan*/  serio; } ;
struct psmouse {scalar_t__ pktcnt; scalar_t__ pktsize; int* packet; TYPE_1__ ps2dev; struct alps_data* private; } ;
struct alps_data {int /*<<< orphan*/  (* process_packet ) (struct psmouse*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int,int,int) ; 
 int /*<<< orphan*/  serio_continue_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_pause_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct psmouse*) ; 

__attribute__((used)) static void alps_flush_packet(unsigned long data)
{
	struct psmouse *psmouse = (struct psmouse *)data;
	struct alps_data *priv = psmouse->private;

	serio_pause_rx(psmouse->ps2dev.serio);

	if (psmouse->pktcnt == psmouse->pktsize) {

		/*
		 * We did not any more data in reasonable amount of time.
		 * Validate the last 3 bytes and process as a standard
		 * ALPS packet.
		 */
		if ((psmouse->packet[3] |
		     psmouse->packet[4] |
		     psmouse->packet[5]) & 0x80) {
			dbg("refusing packet %x %x %x "
			    "(suspected interleaved ps/2)\n",
			    psmouse->packet[3], psmouse->packet[4],
			    psmouse->packet[5]);
		} else {
			priv->process_packet(psmouse);
		}
		psmouse->pktcnt = 0;
	}

	serio_continue_rx(psmouse->ps2dev.serio);
}