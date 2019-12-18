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
 int /*<<< orphan*/  EL_STATUS ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int get_token(const char *buff, char *dest, int len)
{
	const char *p = buff;
	char sep = ' ';
	int d = 0, skip = 0;

	while (*p && *p == ' ') {
		skip++;
		p++;
	}

	if (*p == '\"') {
		sep = '\"';
		p++;
	}
	while (*p && *p != sep && d < len-1)
		dest[d++] = *p++;
	dest[d] = 0;

	if (sep == '\"' && *p != sep)
		elprintf(EL_STATUS, "cue: bad token: \"%s\"", buff);

	return d + skip;
}