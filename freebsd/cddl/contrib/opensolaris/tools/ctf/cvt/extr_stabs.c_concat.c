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
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* xrealloc (char*,int) ; 

__attribute__((used)) static char *
concat(char *s1, char *s2, int s2strip)
{
	int savelen = strlen(s2) - s2strip;
	int newlen = (s1 ? strlen(s1) : 0) + savelen + 1;
	char *out;

	out = xrealloc(s1, newlen);
	if (s1)
		strncpy(out + strlen(out), s2, savelen);
	else
		strncpy(out, s2, savelen);

	out[newlen - 1] = '\0';

	return (out);
}