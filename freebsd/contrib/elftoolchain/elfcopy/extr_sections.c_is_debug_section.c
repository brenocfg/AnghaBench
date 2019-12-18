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
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_debug_section(const char *name)
{
	const char *dbg_sec[] = {
		".apple_",
		".debug",
		".gnu.linkonce.wi.",
		".line",
		".stab",
		NULL
	};
	const char **p;

	for(p = dbg_sec; *p; p++) {
		if (strncmp(name, *p, strlen(*p)) == 0)
			return (1);
	}

	return (0);
}