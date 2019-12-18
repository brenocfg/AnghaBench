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
prcalled(char *dest, u_char * p)
{
	int l;
	char *dp = dest;

	p++;
	l = *p++ - 1;
	dp += sprintf(dp, "    octet 3 ");
	dp += prbits(dp, *p++, 8, 8);
	*dp++ = '\n';
	dp += sprintf(dp, "    number digits ");
	while (l--)
		*dp++ = *p++;
	*dp++ = '\n';
	return (dp - dest);
}