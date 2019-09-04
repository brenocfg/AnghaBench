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
 int TZNAME_MAX ; 

__attribute__((used)) static void getname(char *d, const char **p)
{
	int i;
	if (**p == '<') {
		++*p;
		for (i=0; **p!='>' && i<TZNAME_MAX; i++)
			d[i] = (*p)[i];
		++*p;
	} else {
		for (i=0; ((*p)[i]|32)-'a'<26U && i<TZNAME_MAX; i++)
			d[i] = (*p)[i];
	}
	*p += i;
	d[i] = 0;
}