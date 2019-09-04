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
struct rlimit {int dummy; } ;
struct ctx {int res; int err; struct rlimit const* rlim; } ;

/* Variables and functions */
 int /*<<< orphan*/  __synccall (int /*<<< orphan*/ ,struct ctx*) ; 
 int /*<<< orphan*/  do_setrlimit ; 
 scalar_t__ errno ; 

int setrlimit(int resource, const struct rlimit *rlim)
{
	struct ctx c = { .res = resource, .rlim = rlim, .err = -1 };
	__synccall(do_setrlimit, &c);
	if (c.err) {
		if (c.err>0) errno = c.err;
		return -1;
	}
	return 0;
}