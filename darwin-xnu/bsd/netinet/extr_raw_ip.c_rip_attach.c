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
struct socket {int so_state; scalar_t__ so_pcb; } ;
struct proc {int dummy; } ;
struct inpcb {int inp_ip_p; int /*<<< orphan*/  inp_ip_ttl; int /*<<< orphan*/  inp_vflag; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  INP_IPV4 ; 
 int SS_PRIV ; 
 int in_pcballoc (struct socket*,int /*<<< orphan*/ *,struct proc*) ; 
 int /*<<< orphan*/  ip_defttl ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rip_recvspace ; 
 int /*<<< orphan*/  rip_sendspace ; 
 int /*<<< orphan*/  ripcbinfo ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
rip_attach(struct socket *so, int proto, struct proc *p)
{
	struct inpcb *inp;
	int error;

	inp = sotoinpcb(so);
	if (inp)
		panic("rip_attach");
	if ((so->so_state & SS_PRIV) == 0)
		return (EPERM);

	error = soreserve(so, rip_sendspace, rip_recvspace);
	if (error)
		return error;
	error = in_pcballoc(so, &ripcbinfo, p);
	if (error)
		return error;
	inp = (struct inpcb *)so->so_pcb;
	inp->inp_vflag |= INP_IPV4;
	inp->inp_ip_p = proto;
	inp->inp_ip_ttl = ip_defttl;
	return 0;
}