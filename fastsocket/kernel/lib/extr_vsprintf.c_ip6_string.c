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
 char* pack_hex_byte (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ip6_string(char *p, const char *addr, const char *fmt)
{
	int i;
	for (i = 0; i < 8; i++) {
		p = pack_hex_byte(p, *addr++);
		p = pack_hex_byte(p, *addr++);
		if (fmt[0] == 'I' && i != 7)
			*p++ = ':';
	}

	*p = '\0';
	return p;
}