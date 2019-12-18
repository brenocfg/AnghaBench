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
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int isdn_getnum(char *p)
{
	int v = -1;

	gig_dbg(DEBUG_TRANSCMD, "string: %s", p);

	while (*p >= '0' && *p <= '9')
		v = ((v < 0) ? 0 : (v * 10)) + (int) ((*p++) - '0');
	if (*p)
		v = -1; /* invalid Character */
	return v;
}