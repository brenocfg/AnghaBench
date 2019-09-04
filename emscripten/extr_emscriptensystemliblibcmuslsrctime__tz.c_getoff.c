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
 int getint (char const**) ; 

__attribute__((used)) static int getoff(const char **p)
{
	int neg = 0;
	if (**p == '-') {
		++*p;
		neg = 1;
	} else if (**p == '+') {
		++*p;
	}
	int off = 3600*getint(p);
	if (**p == ':') {
		++*p;
		off += 60*getint(p);
		if (**p == ':') {
			++*p;
			off += getint(p);
		}
	}
	return neg ? -off : off;
}