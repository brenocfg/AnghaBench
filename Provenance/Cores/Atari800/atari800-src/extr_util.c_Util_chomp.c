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
 int strlen (char*) ; 

void Util_chomp(char *s)
{
	int len;

	len = strlen(s);
	if (len >= 2 && s[len - 1] == '\n' && s[len - 2] == '\r')
		s[len - 2] = '\0';
	else if (len >= 1 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
		s[len - 1] = '\0';
}