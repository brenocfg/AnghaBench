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
 char* parse_dup_count (char const*,int*) ; 

__attribute__((used)) static const char *parse_dup(const char *s, int ere, int *pmin, int *pmax)
{
	int min, max;

	s = parse_dup_count(s, &min);
	if (*s == ',')
		s = parse_dup_count(s+1, &max);
	else
		max = min;

	if (
		(max < min && max >= 0) ||
		max > RE_DUP_MAX ||
		min > RE_DUP_MAX ||
		min < 0 ||
		(!ere && *s++ != '\\') ||
		*s++ != '}'
	)
		return 0;
	*pmin = min;
	*pmax = max;
	return s;
}