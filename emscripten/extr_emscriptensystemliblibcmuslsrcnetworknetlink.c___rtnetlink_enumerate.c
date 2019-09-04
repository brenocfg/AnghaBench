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

/* Variables and functions */
 int /*<<< orphan*/  NETLINK_ROUTE ; 
 int /*<<< orphan*/  PF_NETLINK ; 
 int /*<<< orphan*/  RTM_GETADDR ; 
 int /*<<< orphan*/  RTM_GETLINK ; 
 int SOCK_CLOEXEC ; 
 int SOCK_RAW ; 
 int /*<<< orphan*/  SYS_close ; 
 int __netlink_enumerate (int,int,int /*<<< orphan*/ ,int,int (*) (void*,struct nlmsghdr*),void*) ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int __rtnetlink_enumerate(int link_af, int addr_af, int (*cb)(void *ctx, struct nlmsghdr *h), void *ctx)
{
	int fd, r;

	fd = socket(PF_NETLINK, SOCK_RAW|SOCK_CLOEXEC, NETLINK_ROUTE);
	if (fd < 0) return -1;
	r = __netlink_enumerate(fd, 1, RTM_GETLINK, link_af, cb, ctx);
	if (!r) r = __netlink_enumerate(fd, 2, RTM_GETADDR, addr_af, cb, ctx);
	__syscall(SYS_close,fd);
	return r;
}