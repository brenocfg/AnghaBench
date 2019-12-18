#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; TYPE_2__ sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct seq_file {int dummy; } ;
struct TYPE_6__ {int ss_family; } ;
struct TCP_Server_Info {TYPE_3__ dstaddr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void
cifs_show_address(struct seq_file *s, struct TCP_Server_Info *server)
{
	struct sockaddr_in *sa = (struct sockaddr_in *) &server->dstaddr;
	struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *) &server->dstaddr;

	seq_printf(s, ",addr=");

	switch (server->dstaddr.ss_family) {
	case AF_INET:
		seq_printf(s, "%pI4", &sa->sin_addr.s_addr);
		break;
	case AF_INET6:
		seq_printf(s, "%pI6", &sa6->sin6_addr.s6_addr);
		if (sa6->sin6_scope_id)
			seq_printf(s, "%%%u", sa6->sin6_scope_id);
		break;
	default:
		seq_printf(s, "(unknown)");
	}
}