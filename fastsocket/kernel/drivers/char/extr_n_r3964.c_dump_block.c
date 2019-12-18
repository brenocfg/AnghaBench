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
 int /*<<< orphan*/  TRACE_PS (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char const) ; 

__attribute__((used)) static void dump_block(const unsigned char *block, unsigned int length)
{
	unsigned int i, j;
	char linebuf[16 * 3 + 1];

	for (i = 0; i < length; i += 16) {
		for (j = 0; (j < 16) && (j + i < length); j++) {
			sprintf(linebuf + 3 * j, "%02x ", block[i + j]);
		}
		linebuf[3 * j] = '\0';
		TRACE_PS("%s", linebuf);
	}
}