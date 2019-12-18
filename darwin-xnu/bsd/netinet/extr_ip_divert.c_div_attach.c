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
typedef  int /*<<< orphan*/  uint64_t ;
struct socket {int /*<<< orphan*/  so_usecount; struct socket* so_pcb; int /*<<< orphan*/  so_state; } ;
struct proc {int dummy; } ;
struct inpcb {int inp_ip_p; struct socket inpcb_mtx; int /*<<< orphan*/  inp_flags; int /*<<< orphan*/  inp_vflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_HDRINCL ; 
 int /*<<< orphan*/  INP_IPV4 ; 
 int /*<<< orphan*/  SS_ISCONNECTED ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  div_recvspace ; 
 int /*<<< orphan*/  div_sendspace ; 
 int /*<<< orphan*/  divcbinfo ; 
 int in_pcballoc (struct socket*,int /*<<< orphan*/ *,struct proc*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int proc_suser (struct proc*) ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
div_attach(struct socket *so, int proto, struct proc *p)
{
	struct inpcb *inp;
	int error;


	inp  = sotoinpcb(so);
	if (inp)
		panic("div_attach");
	if ((error = proc_suser(p)) != 0)
		return error;

	error = soreserve(so, div_sendspace, div_recvspace);
	if (error)
		return error;
	error = in_pcballoc(so, &divcbinfo, p);
	if (error)
		return error;
	inp = (struct inpcb *)so->so_pcb;
	inp->inp_ip_p = proto;
	inp->inp_vflag |= INP_IPV4;
	inp->inp_flags |= INP_HDRINCL;
	/* The socket is always "connected" because
	   we always know "where" to send the packet */
	so->so_state |= SS_ISCONNECTED;

#ifdef MORE_DICVLOCK_DEBUG
	printf("div_attach: so=0x%llx sopcb=0x%llx lock=0x%llx ref=%x\n",
	    (uint64_t)VM_KERNEL_ADDRPERM(so),
	    (uint64_t)VM_KERNEL_ADDRPERM(so->so_pcb),
	    (uint64_t)VM_KERNEL_ADDRPERM(&(sotoinpcb(so)->inpcb_mtx)),
	    so->so_usecount);
#endif
	return 0;
}