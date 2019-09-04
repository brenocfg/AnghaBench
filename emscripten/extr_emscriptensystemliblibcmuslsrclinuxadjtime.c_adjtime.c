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
struct timex {int offset; int /*<<< orphan*/  modes; int /*<<< orphan*/  member_0; } ;
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJ_OFFSET_SINGLESHOT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYS_adjtimex ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,struct timex*) ; 

int adjtime(const struct timeval *in, struct timeval *out)
{
	struct timex tx = { 0 };
	if (in) {
		if (in->tv_sec > 1000 || in->tv_usec > 1000000000) {
			errno = EINVAL;
			return -1;
		}
		tx.offset = in->tv_sec*1000000 + in->tv_usec;
		tx.modes = ADJ_OFFSET_SINGLESHOT;
	}
	if (syscall(SYS_adjtimex, &tx) < 0) return -1;
	if (out) {
		out->tv_sec = tx.offset / 1000000;
		if ((out->tv_usec = tx.offset % 1000000) < 0) {
			out->tv_sec--;
			out->tv_usec += 1000000;
		}
	}
	return 0;
}