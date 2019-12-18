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
 int ISDN_MSNLEN ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static void
isdn_tty_getdial(char *p, char *q,int cnt)
{
	int first = 1;
	int limit = ISDN_MSNLEN - 1;	/* MUST match the size of interface var to avoid
					buffer overflow */

	while (strchr(" 0123456789,#.*WPTSR-", *p) && *p && --cnt>0) {
		if ((*p >= '0' && *p <= '9') || ((*p == 'S') && first) ||
		    ((*p == 'R') && first) ||
		    (*p == '*') || (*p == '#')) {
			*q++ = *p;
			limit--;
		}
		if(!limit)
			break;
		p++;
		first = 0;
	}
	*q = 0;
}