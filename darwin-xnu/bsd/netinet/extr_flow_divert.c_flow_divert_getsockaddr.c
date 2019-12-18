#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int so_flags; TYPE_2__* so_proto; struct flow_divert_pcb* so_fd_pcb; } ;
struct sockaddr {int dummy; } ;
struct flow_divert_pcb {int /*<<< orphan*/  local_address; } ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {TYPE_1__* pr_domain; } ;
struct TYPE_3__ {int /*<<< orphan*/  dom_family; } ;

/* Variables and functions */
 int SOF_FLOW_DIVERT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  flow_divert_dup_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr**) ; 

__attribute__((used)) static errno_t
flow_divert_getsockaddr(struct socket *so, struct sockaddr **sa)
{
	struct flow_divert_pcb	*fd_cb	= so->so_fd_pcb;

	VERIFY((so->so_flags & SOF_FLOW_DIVERT) && so->so_fd_pcb != NULL);

	return flow_divert_dup_addr(so->so_proto->pr_domain->dom_family, 
	                            fd_cb->local_address,
	                            sa);
}