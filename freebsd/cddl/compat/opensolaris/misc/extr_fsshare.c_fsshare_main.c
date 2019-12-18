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
typedef  int /*<<< orphan*/  tmpfile ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 char* FILE_HEADER ; 
 int /*<<< orphan*/  LOCK_EX ; 
 int /*<<< orphan*/  LOCK_UN ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int flock (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int mkstemp (char*) ; 
 int rename (char*,char const*) ; 
 int /*<<< orphan*/  restart_mountd () ; 
 int strlcat (char*,char*,int) ; 
 int strlcpy (char*,char const*,int) ; 
 char* translate_opts (char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 char* zgetline (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
fsshare_main(const char *file, const char *mountpoint, const char *shareopts,
    int share)
{
	char tmpfile[PATH_MAX];
	char *line;
	FILE *newfd, *oldfd;
	int fd, error;

	newfd = oldfd = NULL;
	error = 0;

	/*
	 * Create temporary file in the same directory, so we can atomically
	 * rename it.
	 */
	if (strlcpy(tmpfile, file, sizeof(tmpfile)) >= sizeof(tmpfile))
		return (ENAMETOOLONG);
	if (strlcat(tmpfile, ".XXXXXXXX", sizeof(tmpfile)) >= sizeof(tmpfile))
		return (ENAMETOOLONG);
	fd = mkstemp(tmpfile);
	if (fd == -1)
		return (errno);
	/*
	 * File name is random, so we don't really need file lock now, but it
	 * will be needed after rename(2).
	 */
	error = flock(fd, LOCK_EX);
	assert(error == 0 || (error == -1 && errno == EOPNOTSUPP));
	newfd = fdopen(fd, "r+");
	assert(newfd != NULL);
	/* Open old exports file. */
	oldfd = fopen(file, "r");
	if (oldfd == NULL) {
		if (share) {
			if (errno != ENOENT) {
				error = errno;
				goto out;
			}
		} else {
			/* If there is no exports file, ignore the error. */
			if (errno == ENOENT)
				errno = 0;
			error = errno;
			goto out;
		}
	} else {
		error = flock(fileno(oldfd), LOCK_EX);
		assert(error == 0 || (error == -1 && errno == EOPNOTSUPP));
		error = 0;
	}

	/* Place big, fat warning at the begining of the file. */
	fprintf(newfd, "%s", FILE_HEADER);
	while (oldfd != NULL && (line = zgetline(oldfd, mountpoint)) != NULL)
		fprintf(newfd, "%s\n", line);
	if (oldfd != NULL && ferror(oldfd) != 0) {
		error = ferror(oldfd);
		goto out;
	}
	if (ferror(newfd) != 0) {
		error = ferror(newfd);
		goto out;
	}
	if (share) {
		fprintf(newfd, "%s\t%s\n", mountpoint,
		    translate_opts(shareopts));
	}

out:
	if (error != 0)
		unlink(tmpfile);
	else {
		if (rename(tmpfile, file) == -1) {
			error = errno;
			unlink(tmpfile);
		} else {
			fflush(newfd);
			/*
			 * Send SIGHUP to mountd, but unlock exports file later.
			 */
			restart_mountd();
		}
	}
	if (oldfd != NULL) {
		flock(fileno(oldfd), LOCK_UN);
		fclose(oldfd);
	}
	if (newfd != NULL) {
		flock(fileno(newfd), LOCK_UN);
		fclose(newfd);
	}
	return (error);
}