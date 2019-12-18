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
 int gdb_cris_strlen (char*) ; 
 char getDebugChar () ; 
 unsigned char hex (char) ; 
 int /*<<< orphan*/  putDebugChar (char) ; 

__attribute__((used)) static void
getpacket(char *buffer)
{
	unsigned char checksum;
	unsigned char xmitcsum;
	int i;
	int count;
	char ch;

	do {
		while((ch = getDebugChar ()) != '$')
			/* Wait for the start character $ and ignore all other characters */;
		checksum = 0;
		xmitcsum = -1;
		count = 0;
		/* Read until a # or the end of the buffer is reached */
		while (count < BUFMAX) {
			ch = getDebugChar();
			if (ch == '#')
				break;
			checksum = checksum + ch;
			buffer[count] = ch;
			count = count + 1;
		}

		if (count >= BUFMAX)
			continue;

		buffer[count] = 0;

		if (ch == '#') {
			xmitcsum = hex(getDebugChar()) << 4;
			xmitcsum += hex(getDebugChar());
			if (checksum != xmitcsum) {
				/* Wrong checksum */
				putDebugChar('-');
			} else {
				/* Correct checksum */
				putDebugChar('+');
				/* If sequence characters are received, reply with them */
				if (buffer[2] == ':') {
					putDebugChar(buffer[0]);
					putDebugChar(buffer[1]);
					/* Remove the sequence characters from the buffer */
					count = gdb_cris_strlen(buffer);
					for (i = 3; i <= count; i++)
						buffer[i - 3] = buffer[i];
				}
			}
		}
	} while (checksum != xmitcsum);
}