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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ ENOTSUP ; 
 scalar_t__ EOPNOTSUPP ; 
 int __accept_nocancel (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 

int
accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
	int ret = __accept_nocancel(s, addr, addrlen);

	/* use ENOTSUP for legacy behavior */
	if (ret < 0 && errno == EOPNOTSUPP)
		errno = ENOTSUP;
	return ret;
}