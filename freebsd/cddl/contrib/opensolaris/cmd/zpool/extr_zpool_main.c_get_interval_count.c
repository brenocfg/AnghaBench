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
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_interval_count(int *argcp, char **argv, unsigned long *iv,
    unsigned long *cnt)
{
	unsigned long interval = 0, count = 0;
	int argc = *argcp, errno;

	/*
	 * Determine if the last argument is an integer or a pool name
	 */
	if (argc > 0 && isdigit(argv[argc - 1][0])) {
		char *end;

		errno = 0;
		interval = strtoul(argv[argc - 1], &end, 10);

		if (*end == '\0' && errno == 0) {
			if (interval == 0) {
				(void) fprintf(stderr, gettext("interval "
				    "cannot be zero\n"));
				usage(B_FALSE);
			}
			/*
			 * Ignore the last parameter
			 */
			argc--;
		} else {
			/*
			 * If this is not a valid number, just plow on.  The
			 * user will get a more informative error message later
			 * on.
			 */
			interval = 0;
		}
	}

	/*
	 * If the last argument is also an integer, then we have both a count
	 * and an interval.
	 */
	if (argc > 0 && isdigit(argv[argc - 1][0])) {
		char *end;

		errno = 0;
		count = interval;
		interval = strtoul(argv[argc - 1], &end, 10);

		if (*end == '\0' && errno == 0) {
			if (interval == 0) {
				(void) fprintf(stderr, gettext("interval "
				    "cannot be zero\n"));
				usage(B_FALSE);
			}

			/*
			 * Ignore the last parameter
			 */
			argc--;
		} else {
			interval = 0;
		}
	}

	*iv = interval;
	*cnt = count;
	*argcp = argc;
}