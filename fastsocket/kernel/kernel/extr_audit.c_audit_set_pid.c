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
struct nlmsghdr {int /*<<< orphan*/  nlmsg_pid; } ;
struct audit_buffer {int /*<<< orphan*/  skb; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct nlmsghdr* nlmsg_hdr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audit_set_pid(struct audit_buffer *ab, pid_t pid)
{
	if (ab) {
		struct nlmsghdr *nlh = nlmsg_hdr(ab->skb);
		nlh->nlmsg_pid = pid;
	}
}