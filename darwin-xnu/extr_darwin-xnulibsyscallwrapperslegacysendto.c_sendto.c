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
 int __sendto_nocancel (int,void const*,size_t,int,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 

ssize_t
sendto(int s, const void *msg, size_t len, int flags, const struct sockaddr *to, socklen_t tolen)
{
	int ret = __sendto_nocancel(s, msg, len, flags, to, tolen);

	/* use ENOTSUP for legacy behavior */
	if (ret < 0 && errno == EOPNOTSUPP)
		errno = ENOTSUP;
	return ret;
}