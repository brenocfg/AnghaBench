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
 int RUNLENMAX ; 
 char getDebugChar () ; 
 char hex_asc_hi (int) ; 
 char hex_asc_lo (int) ; 
 scalar_t__ kgdb_started ; 
 int /*<<< orphan*/  putDebugChar (char) ; 

__attribute__((used)) static void
putpacket(char *buffer)
{
	int checksum;
	int runlen;
	int encode;

	do {
		char *src = buffer;
		putDebugChar('$');
		checksum = 0;
		while (*src) {
			/* Do run length encoding */
			putDebugChar(*src);
			checksum += *src;
			runlen = 0;
			while (runlen < RUNLENMAX && *src == src[runlen]) {
				runlen++;
			}
			if (runlen > 3) {
				/* Got a useful amount */
				putDebugChar ('*');
				checksum += '*';
				encode = runlen + ' ' - 4;
				putDebugChar(encode);
				checksum += encode;
				src += runlen;
			} else {
				src++;
			}
		}
		putDebugChar('#');
		putDebugChar(hex_asc_hi(checksum));
		putDebugChar(hex_asc_lo(checksum));
	} while(kgdb_started && (getDebugChar() != '+'));
}