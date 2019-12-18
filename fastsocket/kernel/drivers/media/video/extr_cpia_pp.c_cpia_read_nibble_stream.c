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
struct TYPE_2__ {int /*<<< orphan*/  phase; } ;
struct parport {int /*<<< orphan*/  name; TYPE_1__ ieee1284; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,...) ; 
 unsigned char EOI ; 
 int /*<<< orphan*/  IEEE1284_PH_REV_DATA ; 
 int /*<<< orphan*/  PARPORT_CONTROL_AUTOFD ; 
 int /*<<< orphan*/  PARPORT_STATUS_ACK ; 
 int /*<<< orphan*/  parport_frob_control (struct parport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parport_read_status (struct parport*) ; 
 scalar_t__ parport_wait_peripheral (struct parport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t cpia_read_nibble_stream(struct parport *port,
			       void *buffer, size_t len,
			       int flags)
{
	int i;
	unsigned char *buf = buffer;
	int endseen = 0;

	for (i=0; i < len; i++) {
		unsigned char nibble[2], byte = 0;
		int j;

		/* Image Data is complete when 4 consecutive EOI bytes (0xff) are seen */
		if (endseen > 3 )
			break;

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

		/* Read lower nibble */
		nibble[0] = parport_read_status (port) >>3;

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

		/* Read upper nibble */
		nibble[1] = parport_read_status (port) >>3;

		/* reassemble the byte */
		for (j = 0; j < 2 ; j++ ) {
			nibble[j] &= ~8;
			if ((nibble[j] & 0x10) == 0)
				nibble[j] |= 8;
			nibble[j] &= 0xf;
		}
		byte = (nibble[0] |(nibble[1] << 4));
		*buf++ = byte;

		if(byte == EOI)
		  endseen++;
		else
		  endseen = 0;
	}
	return i;
}