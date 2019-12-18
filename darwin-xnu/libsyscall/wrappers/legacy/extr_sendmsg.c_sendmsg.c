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
struct msghdr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ ENOTSUP ; 
 scalar_t__ EOPNOTSUPP ; 
 int __sendmsg_nocancel (int,struct msghdr const*,int) ; 
 scalar_t__ errno ; 

ssize_t
sendmsg(int s, const struct msghdr *msg, int flags)
{
	int ret = __sendmsg_nocancel(s, msg, flags);

	/* use ENOTSUP for legacy behavior */
	if (ret < 0 && errno == EOPNOTSUPP)
		errno = ENOTSUP;
	return ret;
}