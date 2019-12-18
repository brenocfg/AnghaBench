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
typedef  int /*<<< orphan*/  user_addr_t ;
struct sockaddr {scalar_t__ sa_len; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 scalar_t__ MIN (unsigned int,scalar_t__) ; 
 int copyout (struct sockaddr*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
copyout_sa(struct sockaddr *fromsa, user_addr_t name, socklen_t *namelen)
{
	int error = 0;
	socklen_t sa_len = 0;
	ssize_t len;

	len = *namelen;
	if (len <= 0 || fromsa == 0) {
		len = 0;
	} else {
#ifndef MIN
#define	MIN(a, b) ((a) > (b) ? (b) : (a))
#endif
		sa_len = fromsa->sa_len;
		len = MIN((unsigned int)len, sa_len);
		error = copyout(fromsa, name, (unsigned)len);
		if (error)
			goto out;
	}
	*namelen = sa_len;
out:
	return (0);
}