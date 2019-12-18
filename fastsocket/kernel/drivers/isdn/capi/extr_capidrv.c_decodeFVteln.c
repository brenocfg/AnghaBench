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
 scalar_t__ isdigit (char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int decodeFVteln(char *teln, unsigned long *bmaskp, int *activep)
{
	unsigned long bmask = 0;
	int active = !0;
	char *s;
	int i;

	if (strncmp(teln, "FV:", 3) != 0)
		return 1;
	s = teln + 3;
	while (*s && *s == ' ') s++;
	if (!*s) return -2;
	if (*s == 'p' || *s == 'P') {
		active = 0;
		s++;
	}
	if (*s == 'a' || *s == 'A') {
		active = !0;
		s++;
	}
	while (*s) {
		int digit1 = 0;
		int digit2 = 0;
		if (!isdigit(*s)) return -3;
		while (isdigit(*s)) { digit1 = digit1*10 + (*s - '0'); s++; }
		if (digit1 <= 0 || digit1 > 30) return -4;
		if (*s == 0 || *s == ',' || *s == ' ') {
			bmask |= (1 << digit1);
			digit1 = 0;
			if (*s) s++;
			continue;
		}
		if (*s != '-') return -5;
		s++;
		if (!isdigit(*s)) return -3;
		while (isdigit(*s)) { digit2 = digit2*10 + (*s - '0'); s++; }
		if (digit2 <= 0 || digit2 > 30) return -4;
		if (*s == 0 || *s == ',' || *s == ' ') {
			if (digit1 > digit2)
				for (i = digit2; i <= digit1 ; i++)
					bmask |= (1 << i);
			else 
				for (i = digit1; i <= digit2 ; i++)
					bmask |= (1 << i);
			digit1 = digit2 = 0;
			if (*s) s++;
			continue;
		}
		return -6;
	}
	if (activep) *activep = active;
	if (bmaskp) *bmaskp = bmask;
	return 0;
}