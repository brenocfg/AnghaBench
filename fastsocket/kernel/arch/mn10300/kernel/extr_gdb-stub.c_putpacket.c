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
 int /*<<< orphan*/  gdbstub_io (char*,...) ; 
 int gdbstub_io_rx_char (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbstub_io_tx_char (char) ; 
 int /*<<< orphan*/  gdbstub_proto (char*,char*) ; 
 unsigned char gdbstub_rx_unget ; 
 char hex_asc_hi (unsigned char) ; 
 char hex_asc_lo (unsigned char) ; 

__attribute__((used)) static int putpacket(char *buffer)
{
	unsigned char checksum;
	unsigned char ch;
	int count;

	/*
	 * $<packet info>#<checksum>.
	 */
	gdbstub_proto("### GDB Tx $'%s'#?? ###\n", buffer);

	do {
		gdbstub_io_tx_char('$');
		checksum = 0;
		count = 0;

		while ((ch = buffer[count]) != 0) {
			gdbstub_io_tx_char(ch);
			checksum += ch;
			count += 1;
		}

		gdbstub_io_tx_char('#');
		gdbstub_io_tx_char(hex_asc_hi(checksum));
		gdbstub_io_tx_char(hex_asc_lo(checksum));

	} while (gdbstub_io_rx_char(&ch, 0),
		 ch == '-' && (gdbstub_io("### GDB Rx NAK\n"), 0),
		 ch != '-' && ch != '+' &&
		 (gdbstub_io("### GDB Rx ??? %02x\n", ch), 0),
		 ch != '+' && ch != '$');

	if (ch == '+') {
		gdbstub_io("### GDB Rx ACK\n");
		return 0;
	}

	gdbstub_io("### GDB Tx Abandoned\n");
	gdbstub_rx_unget = ch;
	return 1;
}