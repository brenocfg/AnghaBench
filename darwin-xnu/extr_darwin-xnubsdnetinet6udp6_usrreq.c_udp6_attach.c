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
struct TYPE_4__ {scalar_t__ sb_hiwat; } ;
struct TYPE_3__ {scalar_t__ sb_hiwat; } ;
struct socket {scalar_t__ so_pcb; TYPE_2__ so_rcv; TYPE_1__ so_snd; } ;
struct proc {int dummy; } ;
struct inpcb {int in6p_hops; int in6p_cksum; int /*<<< orphan*/  inp_ip_ttl; int /*<<< orphan*/  inp_vflag; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INP_IPV4 ; 
 int /*<<< orphan*/  INP_IPV6 ; 
 int in_pcballoc (struct socket*,int /*<<< orphan*/ *,struct proc*) ; 
 scalar_t__ ip6_mapped_addr_on ; 
 int /*<<< orphan*/  ip_defttl ; 
 scalar_t__ nstat_collect ; 
 int /*<<< orphan*/  nstat_udp_new_pcb (struct inpcb*) ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  udbinfo ; 
 int /*<<< orphan*/  udp_recvspace ; 
 int /*<<< orphan*/  udp_sendspace ; 

__attribute__((used)) static int
udp6_attach(struct socket *so, int proto, struct proc *p)
{
#pragma unused(proto)
	struct inpcb *inp;
	int error;

	inp = sotoinpcb(so);
	if (inp != NULL)
		return (EINVAL);

	error = in_pcballoc(so, &udbinfo, p);
	if (error)
		return (error);

	if (so->so_snd.sb_hiwat == 0 || so->so_rcv.sb_hiwat == 0) {
		error = soreserve(so, udp_sendspace, udp_recvspace);
		if (error)
			return (error);
	}
	inp = (struct inpcb *)so->so_pcb;
	inp->inp_vflag |= INP_IPV6;
	if (ip6_mapped_addr_on)
		inp->inp_vflag |= INP_IPV4;
	inp->in6p_hops = -1;	/* use kernel default */
	inp->in6p_cksum = -1;	/* just to be sure */
	/*
	 * XXX: ugly!!
	 * IPv4 TTL initialization is necessary for an IPv6 socket as well,
	 * because the socket may be bound to an IPv6 wildcard address,
	 * which may match an IPv4-mapped IPv6 address.
	 */
	inp->inp_ip_ttl = ip_defttl;
	if (nstat_collect)
		nstat_udp_new_pcb(inp);
	return (0);
}