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
typedef  scalar_t__ uint32_t ;
struct socket {struct flow_divert_pcb* so_fd_pcb; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct inpcb {int dummy; } ;
struct flow_divert_pcb {int dummy; } ;
typedef  scalar_t__ mbuf_t ;
typedef  int errno_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int flow_divert_data_out (struct socket*,int,scalar_t__,struct sockaddr*,scalar_t__,struct proc*) ; 
 int flow_divert_pcb_init (struct socket*,scalar_t__) ; 
 int /*<<< orphan*/  mbuf_free (scalar_t__) ; 
 int /*<<< orphan*/  mbuf_freem (scalar_t__) ; 
 scalar_t__ necp_socket_get_flow_divert_control_unit (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

errno_t
flow_divert_implicit_data_out(struct socket *so, int flags, mbuf_t data, struct sockaddr *to, mbuf_t control, struct proc *p)
{
        struct flow_divert_pcb  *fd_cb  = so->so_fd_pcb;
	struct inpcb *inp;
        int error = 0;

	inp = sotoinpcb(so);
	if (inp == NULL) {
		return (EINVAL);
	}

        if (fd_cb == NULL) {
                uint32_t fd_ctl_unit = necp_socket_get_flow_divert_control_unit(inp);
                if (fd_ctl_unit > 0) {
                        error = flow_divert_pcb_init(so, fd_ctl_unit);
                        fd_cb  = so->so_fd_pcb;
                        if (error != 0 || fd_cb == NULL) {
                                goto done;
                        }
                } else {
                        error = ENETDOWN;
                        goto done;
                }
        }
        return flow_divert_data_out(so, flags, data, to, control, p);

done:
        if (data) {
                mbuf_freem(data);
        }
        if (control) {
                mbuf_free(control);
        }

        return error;
}