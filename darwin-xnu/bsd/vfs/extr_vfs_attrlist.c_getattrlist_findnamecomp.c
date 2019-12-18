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
typedef  int ssize_t ;

/* Variables and functions */

__attribute__((used)) static void
getattrlist_findnamecomp(const char *mn, const char **np, ssize_t *nl)
{
	int		counting;
	const char	*cp;

	/*
	 * We're looking for the last sequence of non / characters, but
	 * not including any trailing / characters.
	 */
	*np = NULL;
	*nl = 0;
	counting = 0;
	for (cp = mn; *cp != 0; cp++) {
		if (!counting) {
			/* start of run of chars */
			if (*cp != '/') {
				*np = cp;
				counting = 1;
			}
		} else {
			/* end of run of chars */
			if (*cp == '/') {
				*nl = cp - *np;
				counting = 0;
			}
		}
	}
	/* need to close run? */
	if (counting)
		*nl = cp - *np;
}