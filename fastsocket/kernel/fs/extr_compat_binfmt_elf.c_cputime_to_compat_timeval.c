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
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct compat_timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  cputime_t ;

/* Variables and functions */
 int /*<<< orphan*/  cputime_to_timeval (int /*<<< orphan*/  const,struct timeval*) ; 

__attribute__((used)) static void cputime_to_compat_timeval(const cputime_t cputime,
				      struct compat_timeval *value)
{
	struct timeval tv;
	cputime_to_timeval(cputime, &tv);
	value->tv_sec = tv.tv_sec;
	value->tv_usec = tv.tv_usec;
}