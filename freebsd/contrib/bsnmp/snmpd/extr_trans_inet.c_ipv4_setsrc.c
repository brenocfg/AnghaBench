#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  a4; } ;
struct port_sock {TYPE_1__ ret_source; } ;
struct msghdr {int /*<<< orphan*/  msg_controllen; } ;
struct in_addr {int dummy; } ;
struct cmsghdr {int /*<<< orphan*/  cmsg_len; int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
 int /*<<< orphan*/  CMSG_SPACE (int) ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_SENDSRCADDR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ipv4_setsrc(struct port_sock *sock, struct msghdr *msg)
{
	struct cmsghdr *cmsg = CMSG_FIRSTHDR(msg);

	/* select outgoing interface by setting source address */
	cmsg->cmsg_level = IPPROTO_IP;
	cmsg->cmsg_type = IP_SENDSRCADDR;
	cmsg->cmsg_len = CMSG_LEN(sizeof(struct in_addr));
	memcpy(CMSG_DATA(cmsg), &sock->ret_source.a4,
	    sizeof(struct in_addr));

	msg->msg_controllen = CMSG_SPACE(sizeof(struct in_addr));
}