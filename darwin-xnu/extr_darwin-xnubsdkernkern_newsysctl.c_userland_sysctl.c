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
struct sysctl_req {size_t oldidx; size_t oldlen; scalar_t__ oldptr; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int sysctl_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int*,int /*<<< orphan*/ ,struct sysctl_req*) ; 

int
userland_sysctl(boolean_t string_is_canonical,
				char *namestring, size_t namestringlen,
				int *name, u_int namelen, struct sysctl_req *req,
                size_t *retval)
{
	int error = 0;
	struct sysctl_req req2;

	do {
	    /* if EAGAIN, reset output cursor */
	    req2 = *req;
	    if (!string_is_canonical)
	        namestring[0] = '\0';

	    error = sysctl_root(FALSE, string_is_canonical, namestring, namestringlen, name, namelen, &req2);
	} while (error == EAGAIN);

	if (error && error != ENOMEM)
		return (error);

	if (retval) {
		if (req2.oldptr && req2.oldidx > req2.oldlen)
			*retval = req2.oldlen;
		else
			*retval = req2.oldidx;
	}
	return (error);
}