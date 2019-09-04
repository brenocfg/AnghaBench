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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  socketcall_cp (int /*<<< orphan*/  (*) (int,struct msghdr*,int),int,struct msghdr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ssize_t recvmsg(int fd, struct msghdr *msg, int flags)
{
	ssize_t r;
#if LONG_MAX > INT_MAX
	struct msghdr h, *orig = msg;
	if (msg) {
		h = *msg;
		h.__pad1 = h.__pad2 = 0;
		msg = &h;
	}
#endif
	r = socketcall_cp(recvmsg, fd, msg, flags, 0, 0, 0);
#if LONG_MAX > INT_MAX
	if (orig) *orig = h;
#endif
	return r;
}