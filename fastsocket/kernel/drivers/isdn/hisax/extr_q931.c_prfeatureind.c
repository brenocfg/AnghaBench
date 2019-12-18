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
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static int
prfeatureind(char *dest, u_char * p)
{
	char *dp = dest;

	p += 2; /* skip id, len */
	dp += sprintf(dp, "    octet 3  ");
	dp += prbits(dp, *p, 8, 8);
	*dp++ = '\n';
	if (!(*p++ & 80)) {
		dp += sprintf(dp, "    octet 4  ");
		dp += prbits(dp, *p++, 8, 8);
		*dp++ = '\n';
	}
	dp += sprintf(dp, "    Status:  ");
	switch (*p) {
		case 0:
			dp += sprintf(dp, "Idle");
			break;
		case 1:
			dp += sprintf(dp, "Active");
			break;
		case 2:
			dp += sprintf(dp, "Prompt");
			break;
		case 3:
			dp += sprintf(dp, "Pending");
			break;
		default:
			dp += sprintf(dp, "(Reserved)");
			break;
	}
	*dp++ = '\n';
	return (dp - dest);
}