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
 char* pack_hex_byte (char*,int) ; 

__attribute__((used)) static char *
mem2hex_nbo(char *buf, unsigned char *mem, int count)
{
	int i;
	int ch;

	mem += count - 1;
	for (i = 0; i < count; i++) {
		ch = *mem--;
		buf = pack_hex_byte(buf, ch);
        }

        /* Terminate properly. */
	*buf = '\0';
	return buf;
}