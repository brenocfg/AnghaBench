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

/* Variables and functions */
 int BUFMAX ; 
 int EIO ; 
 int /*<<< orphan*/  gdbstub_io (char*) ; 
 int gdbstub_io_rx_char (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbstub_io_tx_char (char) ; 
 int /*<<< orphan*/  gdbstub_proto (char*,...) ; 
 unsigned char hex (unsigned char) ; 

__attribute__((used)) static void getpacket(char *buffer)
{
	unsigned char checksum;
	unsigned char xmitcsum;
	unsigned char ch;
	int count, i, ret, error;

	for (;;) {
		/*
		 * wait around for the start character,
		 * ignore all other characters
		 */
		do {
			gdbstub_io_rx_char(&ch, 0);
		} while (ch != '$');

		checksum = 0;
		xmitcsum = -1;
		count = 0;
		error = 0;

		/*
		 * now, read until a # or end of buffer is found
		 */
		while (count < BUFMAX) {
			ret = gdbstub_io_rx_char(&ch, 0);
			if (ret < 0)
				error = ret;

			if (ch == '#')
				break;
			checksum += ch;
			buffer[count] = ch;
			count++;
		}

		if (error == -EIO) {
			gdbstub_proto("### GDB Rx Error - Skipping packet"
				      " ###\n");
			gdbstub_proto("### GDB Tx NAK\n");
			gdbstub_io_tx_char('-');
			continue;
		}

		if (count >= BUFMAX || error)
			continue;

		buffer[count] = 0;

		/* read the checksum */
		ret = gdbstub_io_rx_char(&ch, 0);
		if (ret < 0)
			error = ret;
		xmitcsum = hex(ch) << 4;

		ret = gdbstub_io_rx_char(&ch, 0);
		if (ret < 0)
			error = ret;
		xmitcsum |= hex(ch);

		if (error) {
			if (error == -EIO)
				gdbstub_io("### GDB Rx Error -"
					   " Skipping packet\n");
			gdbstub_io("### GDB Tx NAK\n");
			gdbstub_io_tx_char('-');
			continue;
		}

		/* check the checksum */
		if (checksum != xmitcsum) {
			gdbstub_io("### GDB Tx NAK\n");
			gdbstub_io_tx_char('-');	/* failed checksum */
			continue;
		}

		gdbstub_proto("### GDB Rx '$%s#%02x' ###\n", buffer, checksum);
		gdbstub_io("### GDB Tx ACK\n");
		gdbstub_io_tx_char('+'); /* successful transfer */

		/*
		 * if a sequence char is present,
		 * reply the sequence ID
		 */
		if (buffer[2] == ':') {
			gdbstub_io_tx_char(buffer[0]);
			gdbstub_io_tx_char(buffer[1]);

			/*
			 * remove sequence chars from buffer
			 */
			count = 0;
			while (buffer[count])
				count++;
			for (i = 3; i <= count; i++)
				buffer[i - 3] = buffer[i];
		}

		break;
	}
}