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
 int gdbstub_busy ; 
 int /*<<< orphan*/  gdbstub_io_tx_char (char) ; 
 int /*<<< orphan*/  gdbstub_io_tx_flush () ; 
 char hex_asc_hi (unsigned char) ; 
 char hex_asc_lo (unsigned char) ; 
 unsigned char* output_buffer ; 

void gdbstub_exit(int status)
{
	unsigned char checksum;
	unsigned char ch;
	int count;

	gdbstub_busy = 1;
	output_buffer[0] = 'W';
	output_buffer[1] = hex_asc_hi(status);
	output_buffer[2] = hex_asc_lo(status);
	output_buffer[3] = 0;

	gdbstub_io_tx_char('$');
	checksum = 0;
	count = 0;

	while ((ch = output_buffer[count]) != 0) {
		gdbstub_io_tx_char(ch);
		checksum += ch;
		count += 1;
	}

	gdbstub_io_tx_char('#');
	gdbstub_io_tx_char(hex_asc_hi(checksum));
	gdbstub_io_tx_char(hex_asc_lo(checksum));

	/* make sure the output is flushed, or else RedBoot might clobber it */
	gdbstub_io_tx_flush();

	gdbstub_busy = 0;
}