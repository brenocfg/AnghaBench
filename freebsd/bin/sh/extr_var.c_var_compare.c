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
 int strcoll (char const* const,char const* const) ; 

__attribute__((used)) static int
var_compare(const void *a, const void *b)
{
	const char *const *sa, *const *sb;

	sa = a;
	sb = b;
	/*
	 * This compares two var=value strings which creates a different
	 * order from what you would probably expect.  POSIX is somewhat
	 * ambiguous on what should be sorted exactly.
	 */
	return strcoll(*sa, *sb);
}