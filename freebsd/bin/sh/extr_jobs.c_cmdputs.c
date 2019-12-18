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
 char CTLARI ; 
 char CTLBACKQ ; 
 char CTLENDARI ; 
 char CTLENDVAR ; 
 char CTLESC ; 
 char CTLQUOTE ; 
 char CTLQUOTEEND ; 
 char CTLQUOTEMARK ; 
 char CTLVAR ; 
 int VSLENGTH ; 
 int VSNORMAL ; 
 int VSTRIMLEFTMAX ; 
 int VSTRIMRIGHTMAX ; 
 int VSTYPE ; 
 char* cmdnextc ; 
 scalar_t__ cmdnleft ; 

__attribute__((used)) static void
cmdputs(const char *s)
{
	const char *p;
	char *q;
	char c;
	int subtype = 0;

	if (cmdnleft <= 0)
		return;
	p = s;
	q = cmdnextc;
	while ((c = *p++) != '\0') {
		if (c == CTLESC)
			*q++ = *p++;
		else if (c == CTLVAR) {
			*q++ = '$';
			if (--cmdnleft > 0)
				*q++ = '{';
			subtype = *p++;
			if ((subtype & VSTYPE) == VSLENGTH && --cmdnleft > 0)
				*q++ = '#';
		} else if (c == '=' && subtype != 0) {
			*q = "}-+?=##%%\0X"[(subtype & VSTYPE) - VSNORMAL];
			if (*q)
				q++;
			else
				cmdnleft++;
			if (((subtype & VSTYPE) == VSTRIMLEFTMAX ||
			    (subtype & VSTYPE) == VSTRIMRIGHTMAX) &&
			    --cmdnleft > 0)
				*q = q[-1], q++;
			subtype = 0;
		} else if (c == CTLENDVAR) {
			*q++ = '}';
		} else if (c == CTLBACKQ || c == CTLBACKQ+CTLQUOTE) {
			cmdnleft -= 5;
			if (cmdnleft > 0) {
				*q++ = '$';
				*q++ = '(';
				*q++ = '.';
				*q++ = '.';
				*q++ = '.';
				*q++ = ')';
			}
		} else if (c == CTLARI) {
			cmdnleft -= 2;
			if (cmdnleft > 0) {
				*q++ = '$';
				*q++ = '(';
				*q++ = '(';
			}
			p++;
		} else if (c == CTLENDARI) {
			if (--cmdnleft > 0) {
				*q++ = ')';
				*q++ = ')';
			}
		} else if (c == CTLQUOTEMARK || c == CTLQUOTEEND)
			cmdnleft++; /* ignore */
		else
			*q++ = c;
		if (--cmdnleft <= 0) {
			*q++ = '.';
			*q++ = '.';
			*q++ = '.';
			break;
		}
	}
	cmdnextc = q;
}