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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  prbits (char*,int,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static
int
prbearer(char *dest, u_char * p)
{
	char *dp = dest, ch;

	p += 2;
	dp += sprintf(dp, "    octet 3  ");
	dp += prbits(dp, *p++, 8, 8);
	*dp++ = '\n';
	dp += sprintf(dp, "    octet 4  ");
	dp += prbits(dp, *p, 8, 8);
	*dp++ = '\n';
	if ((*p++ & 0x1f) == 0x18) {
		dp += sprintf(dp, "    octet 4.1 ");
		dp += prbits(dp, *p++, 8, 8);
		*dp++ = '\n';
	}
	/* check for user information layer 1 */
	if ((*p & 0x60) == 0x20) {
		ch = ' ';
		do {
			dp += sprintf(dp, "    octet 5%c ", ch);
			dp += prbits(dp, *p, 8, 8);
			*dp++ = '\n';
			if (ch == ' ')
				ch = 'a';
			else
				ch++;
		}
		while (!(*p++ & 0x80));
	}
	/* check for user information layer 2 */
	if ((*p & 0x60) == 0x40) {
		dp += sprintf(dp, "    octet 6  ");
		dp += prbits(dp, *p++, 8, 8);
		*dp++ = '\n';
	}
	/* check for user information layer 3 */
	if ((*p & 0x60) == 0x60) {
		dp += sprintf(dp, "    octet 7  ");
		dp += prbits(dp, *p++, 8, 8);
		*dp++ = '\n';
	}
	return (dp - dest);
}