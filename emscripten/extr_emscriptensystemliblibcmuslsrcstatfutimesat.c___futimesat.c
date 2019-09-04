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
struct timeval {unsigned long long tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int __syscall_ret (int /*<<< orphan*/ ) ; 
 int utimensat (int,char const*,struct timespec*,int /*<<< orphan*/ ) ; 

int __futimesat(int dirfd, const char *pathname, const struct timeval times[2])
{
	struct timespec ts[2];
	if (times) {
		int i;
		for (i=0; i<2; i++) {
			if (times[i].tv_usec >= 1000000ULL)
				return __syscall_ret(-EINVAL);
			ts[i].tv_sec = times[i].tv_sec;
			ts[i].tv_nsec = times[i].tv_usec * 1000;
		}
	}
	return utimensat(dirfd, pathname, times ? ts : 0, 0);
}