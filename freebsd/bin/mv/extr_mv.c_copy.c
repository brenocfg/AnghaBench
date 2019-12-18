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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
#define  EXEC_FAILED 128 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  _PATH_CP ; 
 int /*<<< orphan*/  _PATH_RM ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,char*,char*,char*,char const*,char const*,...) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 scalar_t__ rmdir (char const*) ; 
 scalar_t__ unlink (char const*) ; 
 scalar_t__ vflg ; 
 int vfork () ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char const*,...) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,char const*,...) ; 

__attribute__((used)) static int
copy(const char *from, const char *to)
{
	struct stat sb;
	int pid, status;

	if (lstat(to, &sb) == 0) {
		/* Destination path exists. */
		if (S_ISDIR(sb.st_mode)) {
			if (rmdir(to) != 0) {
				warn("rmdir %s", to);
				return (1);
			}
		} else {
			if (unlink(to) != 0) {
				warn("unlink %s", to);
				return (1);
			}
		}
	} else if (errno != ENOENT) {
		warn("%s", to);
		return (1);
	}

	/* Copy source to destination. */
	if (!(pid = vfork())) {
		execl(_PATH_CP, "mv", vflg ? "-PRpv" : "-PRp", "--", from, to,
		    (char *)NULL);
		_exit(EXEC_FAILED);
	}
	if (waitpid(pid, &status, 0) == -1) {
		warn("%s %s %s: waitpid", _PATH_CP, from, to);
		return (1);
	}
	if (!WIFEXITED(status)) {
		warnx("%s %s %s: did not terminate normally",
		    _PATH_CP, from, to);
		return (1);
	}
	switch (WEXITSTATUS(status)) {
	case 0:
		break;
	case EXEC_FAILED:
		warnx("%s %s %s: exec failed", _PATH_CP, from, to);
		return (1);
	default:
		warnx("%s %s %s: terminated with %d (non-zero) status",
		    _PATH_CP, from, to, WEXITSTATUS(status));
		return (1);
	}

	/* Delete the source. */
	if (!(pid = vfork())) {
		execl(_PATH_RM, "mv", "-rf", "--", from, (char *)NULL);
		_exit(EXEC_FAILED);
	}
	if (waitpid(pid, &status, 0) == -1) {
		warn("%s %s: waitpid", _PATH_RM, from);
		return (1);
	}
	if (!WIFEXITED(status)) {
		warnx("%s %s: did not terminate normally", _PATH_RM, from);
		return (1);
	}
	switch (WEXITSTATUS(status)) {
	case 0:
		break;
	case EXEC_FAILED:
		warnx("%s %s: exec failed", _PATH_RM, from);
		return (1);
	default:
		warnx("%s %s: terminated with %d (non-zero) status",
		    _PATH_RM, from, WEXITSTATUS(status));
		return (1);
	}
	return (0);
}