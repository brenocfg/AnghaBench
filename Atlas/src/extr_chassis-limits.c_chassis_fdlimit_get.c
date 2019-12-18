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
struct rlimit {int rlim_cur; } ;
typedef  int gint64 ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int _getmaxstdio () ; 
 int getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

gint64 chassis_fdlimit_get() {
#ifdef _WIN32
	return _getmaxstdio();
#else
	struct rlimit max_files_rlimit;

	if (-1 == getrlimit(RLIMIT_NOFILE, &max_files_rlimit)) {
		return -1;
	} else {
		return max_files_rlimit.rlim_cur;
	}
#endif

}