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
struct stat {int dummy; } ;

/* Variables and functions */
 char* BINDIR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lstat (char*,struct stat*) ; 
 char* perf_exec_path () ; 
 int run_dir (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

int test__attr(void)
{
	struct stat st;
	char path_perf[PATH_MAX];
	char path_dir[PATH_MAX];

	/* First try developement tree tests. */
	if (!lstat("./tests", &st))
		return run_dir("./tests", "./perf");

	/* Then installed path. */
	snprintf(path_dir,  PATH_MAX, "%s/tests", perf_exec_path());
	snprintf(path_perf, PATH_MAX, "%s/perf", BINDIR);

	if (!lstat(path_dir, &st) &&
	    !lstat(path_perf, &st))
		return run_dir(path_dir, path_perf);

	fprintf(stderr, " (ommitted)");
	return 0;
}