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
 char** argptr ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  minus_o (char*,int) ; 
 char* minusc ; 
 int /*<<< orphan*/  setoption (int,int) ; 
 int /*<<< orphan*/  setparam (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ vflag ; 
 scalar_t__ xflag ; 

__attribute__((used)) static void
options(int cmdline)
{
	char *kp, *p;
	int val;
	int c;

	if (cmdline)
		minusc = NULL;
	while ((p = *argptr) != NULL) {
		argptr++;
		if ((c = *p++) == '-') {
			val = 1;
			/* A "-" or  "--" terminates options */
			if (p[0] == '\0')
				goto end_options1;
			if (p[0] == '-' && p[1] == '\0')
				goto end_options2;
			/**
			 * For the benefit of `#!' lines in shell scripts,
			 * treat a string of '-- *#.*' the same as '--'.
			 * This is needed so that a script starting with:
			 *	#!/bin/sh -- # -*- perl -*-
			 * will continue to work after a change is made to
			 * kern/imgact_shell.c to NOT token-ize the options
			 * specified on a '#!' line.  A bit of a kludge,
			 * but that trick is recommended in documentation
			 * for some scripting languages, and we might as
			 * well continue to support it.
			 */
			if (p[0] == '-') {
				kp = p + 1;
				while (*kp == ' ' || *kp == '\t')
					kp++;
				if (*kp == '#' || *kp == '\0')
					goto end_options2;
			}
		} else if (c == '+') {
			val = 0;
		} else {
			argptr--;
			break;
		}
		while ((c = *p++) != '\0') {
			if (c == 'c' && cmdline) {
				char *q;

				q = *argptr++;
				if (q == NULL || minusc != NULL)
					error("Bad -c option");
				minusc = q;
			} else if (c == 'o') {
				minus_o(*argptr, val);
				if (*argptr)
					argptr++;
			} else
				setoption(c, val);
		}
	}
	return;

	/* When processing `set', a single "-" means turn off -x and -v */
end_options1:
	if (!cmdline) {
		xflag = vflag = 0;
		return;
	}

	/*
	 * When processing `set', a "--" means the remaining arguments
	 * replace the positional parameters in the active shell.  If
	 * there are no remaining options, then all the positional
	 * parameters are cleared (equivalent to doing ``shift $#'').
	 */
end_options2:
	if (!cmdline) {
		if (*argptr == NULL)
			setparam(0, argptr);
		return;
	}

	/*
	 * At this point we are processing options given to 'sh' on a command
	 * line.  If an end-of-options marker ("-" or "--") is followed by an
	 * arg of "#", then skip over all remaining arguments.  Some scripting
	 * languages (e.g.: perl) document that /bin/sh will implement this
	 * behavior, and they recommend that users take advantage of it to
	 * solve certain issues that can come up when writing a perl script.
	 * Yes, this feature is in /bin/sh to help users write perl scripts.
	 */
	p = *argptr;
	if (p != NULL && p[0] == '#' && p[1] == '\0') {
		while (*argptr != NULL)
			argptr++;
		/* We need to keep the final argument */
		argptr--;
	}
}