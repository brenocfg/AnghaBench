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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static char *bits_names(unsigned int bits, char *names[], int size)
{
	int i, n;
	static char buf[128];

	for (i = 0, n = 0; i < size; i++) {
		if (bits & (1U<<i) && names[i])
			n += snprintf(buf + n, sizeof(buf) - n, " %s",
				      names[i]);
	}
	buf[n] = '\0';

	return buf;
}