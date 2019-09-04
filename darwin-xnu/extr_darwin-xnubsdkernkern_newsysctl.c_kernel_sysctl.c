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
typedef  int /*<<< orphan*/  u_int ;
struct sysctl_req {size_t oldlen; size_t newlen; int lock; size_t oldidx; int /*<<< orphan*/  newfunc; int /*<<< orphan*/  oldfunc; void* newptr; void* oldptr; struct proc* p; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 void* CAST_USER_ADDR_T (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (struct sysctl_req*,int) ; 
 int /*<<< orphan*/  sysctl_new_kernel ; 
 int /*<<< orphan*/  sysctl_old_kernel ; 
 int sysctl_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,struct sysctl_req*) ; 

int
kernel_sysctl(struct proc *p, int *name, u_int namelen, void *old, size_t *oldlenp, void *new, size_t newlen)
{
	int error = 0;
	struct sysctl_req req;

	/*
	 * Construct request.
	 */
	bzero(&req, sizeof req);
	req.p = p;
	if (oldlenp)
		req.oldlen = *oldlenp;
	if (old)
		req.oldptr = CAST_USER_ADDR_T(old);
	if (newlen) {
		req.newlen = newlen;
		req.newptr = CAST_USER_ADDR_T(new);
	}
	req.oldfunc = sysctl_old_kernel;
	req.newfunc = sysctl_new_kernel;
	req.lock = 1;

	/* make the request */
	error = sysctl_root(TRUE, FALSE, NULL, 0, name, namelen, &req);

	if (error && error != ENOMEM)
		return (error);

	if (oldlenp)
		*oldlenp = req.oldidx;

	return (error);
}