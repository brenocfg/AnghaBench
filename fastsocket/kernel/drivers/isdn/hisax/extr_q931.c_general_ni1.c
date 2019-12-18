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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  prbits (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char) ; 

__attribute__((used)) static int
general_ni1(char *dest, u_char * p)
{
	char *dp = dest;
	char ch = ' ';
	int l, octet = 3;

	p++;
	l = *p++;
	/* Iterate over all octets in the information element */
	while (l--) {
		dp += sprintf(dp, "    octet %d%c ", octet, ch);
		dp += prbits(dp, *p, 8, 8);
		*dp++ = '\n';

		/* last octet in group? */
		if (*p++ & 0x80) {
			octet++;
			ch = ' ';
		} else if (ch == ' ')
			ch = 'a';
		else
			ch++;
	}
	return (dp - dest);
}