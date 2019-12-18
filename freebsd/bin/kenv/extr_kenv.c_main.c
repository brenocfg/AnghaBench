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
 scalar_t__ Nflag ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ hflag ; 
 int kdumpenv () ; 
 int kgetenv (char*) ; 
 int ksetenv (char*,char*) ; 
 int kunsetenv (char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  qflag ; 
 char* strchr (char*,char) ; 
 scalar_t__ uflag ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 

int
main(int argc, char **argv)
{
	char *env, *eq, *val;
	int ch, error;

	val = NULL;
	env = NULL;
	while ((ch = getopt(argc, argv, "hNquv")) != -1) {
		switch (ch) {
		case 'h':
			hflag++;
			break;
		case 'N':
			Nflag++;
			break;
		case 'q':
			qflag++;
			break;
		case 'u':
			uflag++;
			break;
		case 'v':
			vflag++;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (argc > 0) {
		env = argv[0];
		eq = strchr(env, '=');
		if (eq != NULL) {
			*eq++ = '\0';
			val = eq;
		}
		argv++;
		argc--;
	}
	if ((hflag || Nflag) && env != NULL)
		usage();
	if (argc > 0 || ((uflag || vflag) && env == NULL))
		usage();
	if (env == NULL) {
		error = kdumpenv();
		if (error && !qflag)
			warn("kdumpenv");
	} else if (val == NULL) {
		if (uflag) {
			error = kunsetenv(env);
			if (error && !qflag)
				warnx("unable to unset %s", env);
		} else {
			error = kgetenv(env);
			if (error && !qflag)
				warnx("unable to get %s", env);
		}
	} else {
		error = ksetenv(env, val);
		if (error && !qflag)
			warnx("unable to set %s to %s", env, val);
	}
	return (error);
}