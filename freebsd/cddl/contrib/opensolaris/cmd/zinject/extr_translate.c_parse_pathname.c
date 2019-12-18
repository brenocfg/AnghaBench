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
struct statfs {char* f_mntonname; char const* f_mntfromname; int /*<<< orphan*/  f_fstypename; } ;
struct stat64 {int dummy; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MNTTYPE_ZFS ; 
 int /*<<< orphan*/  compress_slashes (char const*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stat64 (char*,struct stat64*) ; 
 int statfs (char*,struct statfs*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int
parse_pathname(const char *inpath, char *dataset, char *relpath,
    struct stat64 *statbuf)
{
	struct statfs sfs;
	const char *rel;
	char fullpath[MAXPATHLEN];

	compress_slashes(inpath, fullpath);

	if (fullpath[0] != '/') {
		(void) fprintf(stderr, "invalid object '%s': must be full "
		    "path\n", fullpath);
		usage();
		return (-1);
	}

	if (strlen(fullpath) >= MAXPATHLEN) {
		(void) fprintf(stderr, "invalid object; pathname too long\n");
		return (-1);
	}

	if (stat64(fullpath, statbuf) != 0) {
		(void) fprintf(stderr, "cannot open '%s': %s\n",
		    fullpath, strerror(errno));
		return (-1);
	}

	if (statfs(fullpath, &sfs) == -1) {
		(void) fprintf(stderr, "cannot find mountpoint for '%s': %s\n",
		    fullpath, strerror(errno));
		return (-1);
	}

	if (strcmp(sfs.f_fstypename, MNTTYPE_ZFS) != 0) {
		(void) fprintf(stderr, "invalid path '%s': not a ZFS "
		    "filesystem\n", fullpath);
		return (-1);
	}

	if (strncmp(fullpath, sfs.f_mntonname, strlen(sfs.f_mntonname)) != 0) {
		(void) fprintf(stderr, "invalid path '%s': mountpoint "
		    "doesn't match path\n", fullpath);
		return (-1);
	}

	(void) strcpy(dataset, sfs.f_mntfromname);

	rel = fullpath + strlen(sfs.f_mntonname);
	if (rel[0] == '/')
		rel++;
	(void) strcpy(relpath, rel);

	return (0);
}