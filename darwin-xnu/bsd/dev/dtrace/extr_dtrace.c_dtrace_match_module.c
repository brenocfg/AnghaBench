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
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
dtrace_match_module(const char *s, const char *p, int depth)
{
#pragma unused(depth) /* __APPLE__ */
	size_t len;
	if (s == NULL || p == NULL)
		return (0);

	len = strlen(p);

	if (strncmp(p, s, len) != 0)
		return (0);

	if (s[len] == '.' || s[len] == '\0')
		return (1);

	return (0);
}