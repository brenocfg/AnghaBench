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
struct stat {int st_mode; int st_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 scalar_t__ ENOENT ; 
 int SF_APPEND ; 
 int SF_IMMUTABLE ; 
 int S_IFWHT ; 
 int S_IRUSR ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISWHT (int) ; 
 int S_IWUSR ; 
 int UF_APPEND ; 
 int UF_IMMUTABLE ; 
 scalar_t__ Wflag ; 
 int /*<<< orphan*/  check (char*,char*,struct stat*) ; 
 int /*<<< orphan*/  dflag ; 
 scalar_t__ errno ; 
 int eval ; 
 int /*<<< orphan*/  fflag ; 
 scalar_t__ info ; 
 int lchflags (char*,int) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rmdir (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid ; 
 int undelete (char*) ; 
 int unlink (char*) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 

__attribute__((used)) static void
rm_file(char **argv)
{
	struct stat sb;
	int rval;
	char *f;

	/*
	 * Remove a file.  POSIX 1003.2 states that, by default, attempting
	 * to remove a directory is an error, so must always stat the file.
	 */
	while ((f = *argv++) != NULL) {
		/* Assume if can't stat the file, can't unlink it. */
		if (lstat(f, &sb)) {
			if (Wflag) {
				sb.st_mode = S_IFWHT|S_IWUSR|S_IRUSR;
			} else {
				if (!fflag || errno != ENOENT) {
					warn("%s", f);
					eval = 1;
				}
				continue;
			}
		} else if (Wflag) {
			warnx("%s: %s", f, strerror(EEXIST));
			eval = 1;
			continue;
		}

		if (S_ISDIR(sb.st_mode) && !dflag) {
			warnx("%s: is a directory", f);
			eval = 1;
			continue;
		}
		if (!fflag && !S_ISWHT(sb.st_mode) && !check(f, f, &sb))
			continue;
		rval = 0;
		if (!uid && !S_ISWHT(sb.st_mode) &&
		    (sb.st_flags & (UF_APPEND|UF_IMMUTABLE)) &&
		    !(sb.st_flags & (SF_APPEND|SF_IMMUTABLE)))
			rval = lchflags(f, sb.st_flags & ~(UF_APPEND|UF_IMMUTABLE));
		if (rval == 0) {
			if (S_ISWHT(sb.st_mode))
				rval = undelete(f);
			else if (S_ISDIR(sb.st_mode))
				rval = rmdir(f);
			else
				rval = unlink(f);
		}
		if (rval && (!fflag || errno != ENOENT)) {
			warn("%s", f);
			eval = 1;
		}
		if (vflag && rval == 0)
			(void)printf("%s\n", f);
		if (info && rval == 0) {
			info = 0;
			(void)printf("%s\n", f);
		}
	}
}