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
struct timespec {int dummy; } ;
struct mmsghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_recvmmsg ; 
 int syscall_cp (int /*<<< orphan*/ ,int,struct mmsghdr*,unsigned int,unsigned int,struct timespec*) ; 

int recvmmsg(int fd, struct mmsghdr *msgvec, unsigned int vlen, unsigned int flags, struct timespec *timeout)
{
#if LONG_MAX > INT_MAX
	struct mmsghdr *mh = msgvec;
	unsigned int i;
	for (i = vlen; i; i--, mh++)
		mh->msg_hdr.__pad1 = mh->msg_hdr.__pad2 = 0;
#endif
	return syscall_cp(SYS_recvmmsg, fd, msgvec, vlen, flags, timeout);
}