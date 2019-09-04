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
 int RE_DUP_MAX ; 
 int /*<<< orphan*/  isdigit (char const) ; 

__attribute__((used)) static const char *parse_dup_count(const char *s, int *n)
{
	*n = -1;
	if (!isdigit(*s))
		return s;
	*n = 0;
	for (;;) {
		*n = 10 * *n + (*s - '0');
		s++;
		if (!isdigit(*s) || *n > RE_DUP_MAX)
			break;
	}
	return s;
}