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
struct psmouse {int pktcnt; int* packet; struct alps_data* private; } ;
struct alps_data {int /*<<< orphan*/  (* process_packet ) (struct psmouse*) ;int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  psmouse_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_BAD_DATA ; 
 int /*<<< orphan*/  PSMOUSE_GOOD_DATA ; 
 int /*<<< orphan*/  alps_is_valid_first_byte (struct alps_data*,int) ; 
 int /*<<< orphan*/  alps_report_bare_ps2_packet (struct psmouse*,int*,int) ; 
 int /*<<< orphan*/  dbg (char*,int,int,int,int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  stub1 (struct psmouse*) ; 

__attribute__((used)) static psmouse_ret_t alps_handle_interleaved_ps2(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;

	if (psmouse->pktcnt < 6)
		return PSMOUSE_GOOD_DATA;

	if (psmouse->pktcnt == 6) {
		/*
		 * Start a timer to flush the packet if it ends up last
		 * 6-byte packet in the stream. Timer needs to fire
		 * psmouse core times out itself. 20 ms should be enough
		 * to decide if we are getting more data or not.
		 */
		mod_timer(&priv->timer, jiffies + msecs_to_jiffies(20));
		return PSMOUSE_GOOD_DATA;
	}

	del_timer(&priv->timer);

	if (psmouse->packet[6] & 0x80) {

		/*
		 * Highest bit is set - that means we either had
		 * complete ALPS packet and this is start of the
		 * next packet or we got garbage.
		 */

		if (((psmouse->packet[3] |
		      psmouse->packet[4] |
		      psmouse->packet[5]) & 0x80) ||
		    (!alps_is_valid_first_byte(priv, psmouse->packet[6]))) {
			dbg("refusing packet %x %x %x %x "
			    "(suspected interleaved ps/2)\n",
			    psmouse->packet[3], psmouse->packet[4],
			    psmouse->packet[5], psmouse->packet[6]);
			return PSMOUSE_BAD_DATA;
		}

		priv->process_packet(psmouse);

		/* Continue with the next packet */
		psmouse->packet[0] = psmouse->packet[6];
		psmouse->pktcnt = 1;

	} else {

		/*
		 * High bit is 0 - that means that we indeed got a PS/2
		 * packet in the middle of ALPS packet.
		 *
		 * There is also possibility that we got 6-byte ALPS
		 * packet followed  by 3-byte packet from trackpoint. We
		 * can not distinguish between these 2 scenarios but
		 * becase the latter is unlikely to happen in course of
		 * normal operation (user would need to press all
		 * buttons on the pad and start moving trackpoint
		 * without touching the pad surface) we assume former.
		 * Even if we are wrong the wost thing that would happen
		 * the cursor would jump but we should not get protocol
		 * desynchronization.
		 */

		alps_report_bare_ps2_packet(psmouse, &psmouse->packet[3],
					    false);

		/*
		 * Continue with the standard ALPS protocol handling,
		 * but make sure we won't process it as an interleaved
		 * packet again, which may happen if all buttons are
		 * pressed. To avoid this let's reset the 4th bit which
		 * is normally 1.
		 */
		psmouse->packet[3] = psmouse->packet[6] & 0xf7;
		psmouse->pktcnt = 4;
	}

	return PSMOUSE_GOOD_DATA;
}