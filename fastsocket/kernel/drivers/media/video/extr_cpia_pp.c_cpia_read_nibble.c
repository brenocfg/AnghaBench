#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phase; } ;
struct parport {TYPE_3__* physport; int /*<<< orphan*/  name; TYPE_1__ ieee1284; } ;
struct TYPE_5__ {int /*<<< orphan*/  phase; } ;
struct TYPE_6__ {TYPE_2__ ieee1284; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  IEEE1284_PH_HBUSY_DAVAIL ; 
 int /*<<< orphan*/  IEEE1284_PH_REV_DATA ; 
 int /*<<< orphan*/  IEEE1284_PH_REV_IDLE ; 
 int /*<<< orphan*/  PARPORT_CONTROL_AUTOFD ; 
 int /*<<< orphan*/  PARPORT_STATUS_ACK ; 
 int PARPORT_STATUS_ERROR ; 
 int /*<<< orphan*/  parport_frob_control (struct parport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parport_read_status (struct parport*) ; 
 scalar_t__ parport_wait_peripheral (struct parport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t cpia_read_nibble (struct parport *port,
			 void *buffer, size_t len,
			 int flags)
{
	/* adapted verbatim, with one change, from
	   parport_ieee1284_read_nibble() in drivers/parport/ieee1284-ops.c */

	unsigned char *buf = buffer;
	int i;
	unsigned char byte = 0;

	len *= 2; /* in nibbles */
	for (i=0; i < len; i++) {
		unsigned char nibble;

		/* The CPiA firmware suppresses the use of nDataAvail (nFault LO)
		 * after every second nibble to signal that more
		 * data is available.  (the total number of Bytes that
		 * should be sent is known; if too few are received, an error
		 * will be recorded after a timeout).
		 * This is incompatible with parport_ieee1284_read_nibble(),
		 * which expects to find nFault LO after every second nibble.
		 */

		/* Solution: modify cpia_read_nibble to only check for
		 * nDataAvail before the first nibble is sent.
		 */

		/* Does the error line indicate end of data? */
		if (((i /*& 1*/) == 0) &&
		    (parport_read_status(port) & PARPORT_STATUS_ERROR)) {
			DBG("%s: No more nibble data (%d bytes)\n",
			    port->name, i/2);
			goto end_of_data;
		}

		/* Event 7: Set nAutoFd low. */
		parport_frob_control (port,
				      PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);

		/* Event 9: nAck goes low. */
		port->ieee1284.phase = IEEE1284_PH_REV_DATA;
		if (parport_wait_peripheral (port,
					     PARPORT_STATUS_ACK, 0)) {
			/* Timeout -- no more data? */
				 DBG("%s: Nibble timeout at event 9 (%d bytes)\n",
				 port->name, i/2);
			parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);
			break;
		}


		/* Read a nibble. */
		nibble = parport_read_status (port) >> 3;
		nibble &= ~8;
		if ((nibble & 0x10) == 0)
			nibble |= 8;
		nibble &= 0xf;

		/* Event 10: Set nAutoFd high. */
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);

		/* Event 11: nAck goes high. */
		if (parport_wait_peripheral (port,
					     PARPORT_STATUS_ACK,
					     PARPORT_STATUS_ACK)) {
			/* Timeout -- no more data? */
			DBG("%s: Nibble timeout at event 11\n",
				 port->name);
			break;
		}

		if (i & 1) {
			/* Second nibble */
			byte |= nibble << 4;
			*buf++ = byte;
		} else
			byte = nibble;
	}

	if (i == len) {
		/* Read the last nibble without checking data avail. */
		if (parport_read_status (port) & PARPORT_STATUS_ERROR) {
		end_of_data:
			/* Go to reverse idle phase. */
			parport_frob_control (port,
					      PARPORT_CONTROL_AUTOFD,
					      PARPORT_CONTROL_AUTOFD);
			port->physport->ieee1284.phase = IEEE1284_PH_REV_IDLE;
		}
		else
			port->physport->ieee1284.phase = IEEE1284_PH_HBUSY_DAVAIL;
	}

	return i/2;
}