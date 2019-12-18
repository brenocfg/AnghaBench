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
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  dt_version_t ;

/* Variables and functions */
 int DT_VERSION_MAJMAX ; 
 int DT_VERSION_MICMAX ; 
 int DT_VERSION_MINMAX ; 
 int /*<<< orphan*/  DT_VERSION_NUMBER (int,int,int) ; 
 scalar_t__ isdigit (char) ; 

int
dt_version_str2num(const char *s, dt_version_t *vp)
{
	int i = 0, n[3] = { 0, 0, 0 };
	char c;

	while ((c = *s++) != '\0') {
		if (isdigit(c))
			n[i] = n[i] * 10 + c - '0';
		else if (c != '.' || i++ >= sizeof (n) / sizeof (n[0]) - 1)
			return (-1);
	}

	if (n[0] > DT_VERSION_MAJMAX ||
	    n[1] > DT_VERSION_MINMAX ||
	    n[2] > DT_VERSION_MICMAX)
		return (-1);

	if (vp != NULL)
		*vp = DT_VERSION_NUMBER(n[0], n[1], n[2]);

	return (0);
}