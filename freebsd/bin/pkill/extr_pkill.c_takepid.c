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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ EWOULDBLOCK ; 
 int LOCK_EX ; 
 int LOCK_NB ; 
 long MAX_PID ; 
 long MIN_PID ; 
 int /*<<< orphan*/  STATUS_ERROR ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ flock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static int
takepid(const char *pidfile, int pidfilelock)
{
	char *endp, line[BUFSIZ];
	FILE *fh;
	long rval;

	fh = fopen(pidfile, "r");
	if (fh == NULL)
		err(STATUS_ERROR, "Cannot open pidfile `%s'", pidfile);

	if (pidfilelock) {
		/*
		 * If we can lock pidfile, this means that daemon is not
		 * running, so would be better not to kill some random process.
		 */
		if (flock(fileno(fh), LOCK_EX | LOCK_NB) == 0) {
			(void)fclose(fh);
			errx(STATUS_ERROR, "File '%s' can be locked", pidfile);
		} else {
			if (errno != EWOULDBLOCK) {
				errx(STATUS_ERROR,
				    "Error while locking file '%s'", pidfile);
			}
		}
	}

	if (fgets(line, sizeof(line), fh) == NULL) {
		if (feof(fh)) {
			(void)fclose(fh);
			errx(STATUS_ERROR, "Pidfile `%s' is empty", pidfile);
		}
		(void)fclose(fh);
		err(STATUS_ERROR, "Cannot read from pid file `%s'", pidfile);
	}
	(void)fclose(fh);

	rval = strtol(line, &endp, 10);
	if (*endp != '\0' && !isspace((unsigned char)*endp))
		errx(STATUS_ERROR, "Invalid pid in file `%s'", pidfile);
	else if (rval < MIN_PID || rval > MAX_PID)
		errx(STATUS_ERROR, "Invalid pid in file `%s'", pidfile);
	return (rval);
}