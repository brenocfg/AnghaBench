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
 char CTLESC ; 
 char CTLQUOTEEND ; 
 char CTLQUOTEMARK ; 

void
rmescapes(char *str)
{
	char *p, *q;

	p = str;
	while (*p != CTLESC && *p != CTLQUOTEMARK && *p != CTLQUOTEEND) {
		if (*p++ == '\0')
			return;
	}
	q = p;
	while (*p) {
		if (*p == CTLQUOTEMARK || *p == CTLQUOTEEND) {
			p++;
			continue;
		}
		if (*p == CTLESC)
			p++;
		*q++ = *p++;
	}
	*q = '\0';
}