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
 int /*<<< orphan*/  DEBUG_TRANSCMD ; 
 int INT_MAX ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int isdn_gethex(char *p)
{
	int v = 0;
	int c;

	gig_dbg(DEBUG_TRANSCMD, "string: %s", p);

	if (!*p)
		return -1;

	do {
		if (v > (INT_MAX - 15) / 16)
			return -1;
		c = *p;
		if (c >= '0' && c <= '9')
			c -= '0';
		else if (c >= 'a' && c <= 'f')
			c -= 'a' - 10;
		else if (c >= 'A' && c <= 'F')
			c -= 'A' - 10;
		else
			return -1;
		v = v * 16 + c;
	} while (*++p);

	return v;
}