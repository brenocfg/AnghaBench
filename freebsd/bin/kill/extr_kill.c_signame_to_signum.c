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
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 int sys_nsig ; 
 int /*<<< orphan*/ * sys_signame ; 

__attribute__((used)) static int
signame_to_signum(const char *sig)
{
	int n;

	if (strncasecmp(sig, "SIG", 3) == 0)
		sig += 3;
	for (n = 1; n < sys_nsig; n++) {
		if (!strcasecmp(sys_signame[n], sig))
			return (n);
	}
	return (-1);
}