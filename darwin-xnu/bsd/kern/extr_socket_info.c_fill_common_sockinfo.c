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
typedef  void* u_int64_t ;
struct socket_info {short soi_options; int /*<<< orphan*/  soi_rcv; int /*<<< orphan*/  soi_snd; int /*<<< orphan*/  soi_oobmark; int /*<<< orphan*/  soi_error; int /*<<< orphan*/  soi_timeo; int /*<<< orphan*/  soi_qlimit; int /*<<< orphan*/  soi_incqlen; int /*<<< orphan*/  soi_qlen; scalar_t__ soi_family; scalar_t__ soi_protocol; void* soi_pcb; int /*<<< orphan*/  soi_state; int /*<<< orphan*/  soi_linger; int /*<<< orphan*/  soi_type; void* soi_so; } ;
struct socket {int so_options; int /*<<< orphan*/  so_rcv; int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_oobmark; int /*<<< orphan*/  so_error; int /*<<< orphan*/  so_timeo; int /*<<< orphan*/  so_qlimit; int /*<<< orphan*/  so_incqlen; int /*<<< orphan*/  so_qlen; TYPE_1__* so_proto; struct socket* so_pcb; int /*<<< orphan*/  so_state; int /*<<< orphan*/  so_linger; int /*<<< orphan*/  so_type; } ;
struct TYPE_2__ {scalar_t__ pr_domain; } ;

/* Variables and functions */
 scalar_t__ SOCK_DOM (struct socket*) ; 
 scalar_t__ SOCK_PROTO (struct socket*) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  fill_sockbuf_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fill_common_sockinfo(struct socket *so, struct socket_info *si)
{
	si->soi_so = (u_int64_t)VM_KERNEL_ADDRPERM(so);
	si->soi_type = so->so_type;
	si->soi_options = (short)(so->so_options & 0xffff);
	si->soi_linger = so->so_linger;
	si->soi_state = so->so_state;
	si->soi_pcb = (u_int64_t)VM_KERNEL_ADDRPERM(so->so_pcb);
	if (so->so_proto) {
		si->soi_protocol = SOCK_PROTO(so);
		if (so->so_proto->pr_domain)
			si->soi_family = SOCK_DOM(so);
		else
			si->soi_family = 0;
	} else {
		si->soi_protocol = si->soi_family = 0;
	}
	si->soi_qlen = so->so_qlen;
	si->soi_incqlen = so->so_incqlen;
	si->soi_qlimit = so->so_qlimit;
	si->soi_timeo = so->so_timeo;
	si->soi_error = so->so_error;
	si->soi_oobmark = so->so_oobmark;
	fill_sockbuf_info(&so->so_snd, &si->soi_snd);
	fill_sockbuf_info(&so->so_rcv, &si->soi_rcv);
}