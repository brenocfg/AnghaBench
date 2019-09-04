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
typedef  void* u_int64_t ;
struct xsocket64 {int xso_len; short so_options; int /*<<< orphan*/  so_uid; int /*<<< orphan*/  so_rcv; int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_oobmark; int /*<<< orphan*/  so_pgid; int /*<<< orphan*/  so_error; int /*<<< orphan*/  so_timeo; int /*<<< orphan*/  so_qlimit; int /*<<< orphan*/  so_incqlen; int /*<<< orphan*/  so_qlen; scalar_t__ xso_family; scalar_t__ xso_protocol; void* so_pcb; int /*<<< orphan*/  so_state; int /*<<< orphan*/  so_linger; int /*<<< orphan*/  so_type; void* xso_so; } ;
struct socket {int so_options; int /*<<< orphan*/  so_cred; int /*<<< orphan*/  so_rcv; int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_oobmark; int /*<<< orphan*/  so_pgid; int /*<<< orphan*/  so_error; int /*<<< orphan*/  so_timeo; int /*<<< orphan*/  so_qlimit; int /*<<< orphan*/  so_incqlen; int /*<<< orphan*/  so_qlen; scalar_t__ so_proto; struct socket* so_pcb; int /*<<< orphan*/  so_state; int /*<<< orphan*/  so_linger; int /*<<< orphan*/  so_type; } ;

/* Variables and functions */
 scalar_t__ SOCK_DOM (struct socket*) ; 
 scalar_t__ SOCK_PROTO (struct socket*) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbtoxsockbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
sotoxsocket64(struct socket *so, struct xsocket64 *xso)
{
	xso->xso_len = sizeof (*xso);
	xso->xso_so = (u_int64_t)VM_KERNEL_ADDRPERM(so);
	xso->so_type = so->so_type;
	xso->so_options = (short)(so->so_options & 0xffff);
	xso->so_linger = so->so_linger;
	xso->so_state = so->so_state;
	xso->so_pcb = (u_int64_t)VM_KERNEL_ADDRPERM(so->so_pcb);
	if (so->so_proto) {
		xso->xso_protocol = SOCK_PROTO(so);
		xso->xso_family = SOCK_DOM(so);
	} else {
		xso->xso_protocol = xso->xso_family = 0;
	}
	xso->so_qlen = so->so_qlen;
	xso->so_incqlen = so->so_incqlen;
	xso->so_qlimit = so->so_qlimit;
	xso->so_timeo = so->so_timeo;
	xso->so_error = so->so_error;
	xso->so_pgid = so->so_pgid;
	xso->so_oobmark = so->so_oobmark;
	sbtoxsockbuf(&so->so_snd, &xso->so_snd);
	sbtoxsockbuf(&so->so_rcv, &xso->so_rcv);
	xso->so_uid = kauth_cred_getuid(so->so_cred);
}