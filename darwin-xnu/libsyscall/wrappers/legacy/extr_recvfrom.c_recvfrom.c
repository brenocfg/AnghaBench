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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ ENOTSUP ; 
 scalar_t__ EOPNOTSUPP ; 
 int __recvfrom_nocancel (int,void*,size_t,int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 

ssize_t
recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr * __restrict from, socklen_t * __restrict fromlen)
{
	int ret = __recvfrom_nocancel(s, buf, len, flags, from, fromlen);

	/* use ENOTSUP for legacy behavior */
	if (ret < 0 && errno == EOPNOTSUPP)
		errno = ENOTSUP;
	return ret;
}