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
struct sockopt {scalar_t__ sopt_name; scalar_t__ sopt_dir; } ;
struct socket {int so_flags; int /*<<< orphan*/  so_traffic_class; struct flow_divert_pcb* so_fd_pcb; } ;
struct flow_divert_pcb {int flags; } ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* pr_ctloutput ) (struct socket*,struct sockopt*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* pr_ctloutput ) (struct socket*,struct sockopt*) ;} ;

/* Variables and functions */
 int FLOW_DIVERT_CONNECT_STARTED ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ SOCK_DOM (struct socket*) ; 
 int SOF_FLOW_DIVERT ; 
 scalar_t__ SOPT_SET ; 
 scalar_t__ SO_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  flow_divert_send_traffic_class_update (struct flow_divert_pcb*,int /*<<< orphan*/ ) ; 
 TYPE_2__* g_tcp6_protosw ; 
 TYPE_1__* g_tcp_protosw ; 
 int /*<<< orphan*/  stub1 (struct socket*,struct sockopt*) ; 
 int /*<<< orphan*/  stub2 (struct socket*,struct sockopt*) ; 

__attribute__((used)) static errno_t
flow_divert_ctloutput(struct socket *so, struct sockopt *sopt)
{
	struct flow_divert_pcb	*fd_cb	= so->so_fd_pcb;

	VERIFY((so->so_flags & SOF_FLOW_DIVERT) && so->so_fd_pcb != NULL);

	if (sopt->sopt_name == SO_TRAFFIC_CLASS) {
		if (sopt->sopt_dir == SOPT_SET && fd_cb->flags & FLOW_DIVERT_CONNECT_STARTED) {
			flow_divert_send_traffic_class_update(fd_cb, so->so_traffic_class);
		}
	}

	if (SOCK_DOM(so) == PF_INET) {
		return g_tcp_protosw->pr_ctloutput(so, sopt);
	}
#if INET6
	else if (SOCK_DOM(so) == PF_INET6) {
		return g_tcp6_protosw->pr_ctloutput(so, sopt);
	}
#endif
	return 0;
}