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
 int /*<<< orphan*/  panic (char*,char const*,char const*,int) ; 

int
dtrace_assfail(const char *a, const char *f, int l)
{
	panic("dtrace: assertion failed: %s, file: %s, line: %d", a, f, l);

	/*
	 * We just need something here that even the most clever compiler
	 * cannot optimize away.
	 */
	return (a[(uintptr_t)f]);
}