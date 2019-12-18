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
 int /*<<< orphan*/  strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
is_sec_debug(const char *shname)
{
	const char *dbg_sec[] = {
		".debug",
		".gnu.linkonce.wi.",
		".line",
		".rel.debug",
		".rela.debug",
		".stab",
		NULL
	};
	const char **p;

	if (shname == NULL)
		return (false);

	for (p = dbg_sec; *p; p++) {
		if (!strncmp(shname, *p, strlen(*p)))
			return (true);
	}

	return (false);
}