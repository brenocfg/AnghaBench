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
 int /*<<< orphan*/  DTRACE_ISALPHA (char) ; 

__attribute__((used)) static int
dtrace_badname(const char *s)
{
	char c;

	if (s == NULL || (c = *s++) == '\0')
		return (0);

	if (!DTRACE_ISALPHA(c) && c != '-' && c != '_' && c != '.')
		return (1);

	while ((c = *s++) != '\0') {
		if (!DTRACE_ISALPHA(c) && (c < '0' || c > '9') &&
		    c != '-' && c != '_' && c != '.' && c != '`')
			return (1);
	}

	return (0);
}