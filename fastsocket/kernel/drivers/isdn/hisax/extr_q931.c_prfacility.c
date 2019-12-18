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
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static int
prfacility(char *dest, u_char * p)
{
	char *dp = dest;
	int l, l2;

	p++;
	l = *p++;
	dp += sprintf(dp, "    octet 3 ");
	dp += prbits(dp, *p++, 8, 8);
	dp += sprintf(dp, "\n");
	l -= 1;

	while (l > 0) {
		dp += sprintf(dp, "   octet 4 ");
		dp += prbits(dp, *p++, 8, 8);
		dp += sprintf(dp, "\n");
		dp += sprintf(dp, "   octet 5 %d\n", l2 = *p++ & 0x7f);
		l -= 2;
		dp += sprintf(dp, "   contents ");
		while (l2--) {
			dp += sprintf(dp, "%2x ", *p++);
			l--;
		}
		dp += sprintf(dp, "\n");
	}

	return (dp - dest);
}