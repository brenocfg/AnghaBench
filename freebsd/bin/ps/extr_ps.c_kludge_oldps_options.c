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
 scalar_t__ isdigitch (char const) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  xo_errx (int,char*) ; 

__attribute__((used)) static char *
kludge_oldps_options(const char *optlist, char *origval, const char *nextarg)
{
	size_t len;
	char *argp, *cp, *newopts, *ns, *optp, *pidp;

	/*
	 * See if the original value includes any option which takes an
	 * argument (and will thus use up the remainder of the string).
	 */
	argp = NULL;
	if (optlist != NULL) {
		for (cp = origval; *cp != '\0'; cp++) {
			optp = strchr(optlist, *cp);
			if ((optp != NULL) && *(optp + 1) == ':') {
				argp = cp;
				break;
			}
		}
	}
	if (argp != NULL && *origval == '-')
		return (origval);

	/*
	 * if last letter is a 't' flag with no argument (in the context
	 * of the oldps options -- option string NOT starting with a '-' --
	 * then convert to 'T' (meaning *this* terminal, i.e. ttyname(0)).
	 *
	 * However, if a flag accepting a string argument is found earlier
	 * in the option string (including a possible `t' flag), then the
	 * remainder of the string must be the argument to that flag; so
	 * do not modify that argument.  Note that a trailing `t' would
	 * cause argp to be set, if argp was not already set by some
	 * earlier option.
	 */
	len = strlen(origval);
	cp = origval + len - 1;
	pidp = NULL;
	if (*cp == 't' && *origval != '-' && cp == argp) {
		if (nextarg == NULL || *nextarg == '-' || isdigitch(*nextarg))
			*cp = 'T';
	} else if (argp == NULL) {
		/*
		 * The original value did not include any option which takes
		 * an argument (and that would include `p' and `t'), so check
		 * the value for trailing number, or comma-separated list of
		 * numbers, which we will treat as a pid request.
		 */
		if (isdigitch(*cp)) {
			while (cp >= origval && (*cp == ',' || isdigitch(*cp)))
				--cp;
			pidp = cp + 1;
		}
	}

	/*
	 * If nothing needs to be added to the string, then return
	 * the "original" (although possibly modified) value.
	 */
	if (*origval == '-' && pidp == NULL)
		return (origval);

	/*
	 * Create a copy of the string to add '-' and/or 'p' to the
	 * original value.
	 */
	if ((newopts = ns = malloc(len + 3)) == NULL)
		xo_errx(1, "malloc failed");

	if (*origval != '-')
		*ns++ = '-';	/* add option flag */

	if (pidp == NULL)
		strcpy(ns, origval);
	else {
		/*
		 * Copy everything before the pid string, add the `p',
		 * and then copy the pid string.
		 */
		len = pidp - origval;
		memcpy(ns, origval, len);
		ns += len;
		*ns++ = 'p';
		strcpy(ns, pidp);
	}

	return (newopts);
}