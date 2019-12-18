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
 scalar_t__ ISSLASH (char*) ; 
 int eval ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
checkslash(char **argv)
{
	char **t, **u;
	int complained;

	complained = 0;
	for (t = argv; *t;) {
		if (ISSLASH(*t)) {
			if (!complained++)
				warnx("\"/\" may not be removed");
			eval = 1;
			for (u = t; u[0] != NULL; ++u)
				u[0] = u[1];
		} else {
			++t;
		}
	}
}