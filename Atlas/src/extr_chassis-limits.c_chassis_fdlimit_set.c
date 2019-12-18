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
struct rlimit {int rlim_cur; int rlim_max; } ;
typedef  int rlim_t ;
typedef  int gint64 ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int _setmaxstdio (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 int getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

int chassis_fdlimit_set(gint64 max_files_number) {
#ifdef _WIN32
	int max_files_number_set;

	max_files_number_set = _setmaxstdio(max_files_number);

	if (-1 == max_files_number_set) {
		return -1;
	} else if (max_files_number_set != max_files_number) {
		g_critical("%s: failed to increase the maximum number of open files for stdio: %s (%d)", G_STRLOC, g_strerror(errno), errno);
		return -1;
	}

	return 0;
#else
	struct rlimit max_files_rlimit;
	rlim_t soft_limit;
	rlim_t hard_limit;

	if (-1 == getrlimit(RLIMIT_NOFILE, &max_files_rlimit)) {
		return -1;
	}

	soft_limit = max_files_rlimit.rlim_cur;
	hard_limit = max_files_rlimit.rlim_max;

	max_files_rlimit.rlim_cur = max_files_number;
	if (hard_limit < max_files_number) { /* raise the hard-limit too in case it is smaller than the soft-limit, otherwise we get a EINVAL */
		max_files_rlimit.rlim_max = max_files_number;
	}

	if (-1 == setrlimit(RLIMIT_NOFILE, &max_files_rlimit)) {
		return -1;
	}

	return 0;
#endif
}