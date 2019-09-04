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
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int utimensat (int /*<<< orphan*/ ,char const*,struct timespec*,int /*<<< orphan*/ ) ; 

int lutimes(const char *filename, const struct timeval tv[2])
{
	struct timespec times[2];
	times[0].tv_sec  = tv[0].tv_sec;
	times[0].tv_nsec = tv[0].tv_usec * 1000;
	times[1].tv_sec  = tv[1].tv_sec;
	times[1].tv_nsec = tv[1].tv_usec * 1000;
	return utimensat(AT_FDCWD, filename, times, AT_SYMLINK_NOFOLLOW);
}