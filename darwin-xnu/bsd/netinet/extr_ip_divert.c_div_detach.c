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
struct socket {int /*<<< orphan*/  so_usecount; struct socket* so_pcb; } ;
struct inpcb {int /*<<< orphan*/  inp_state; struct socket inpcb_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPCB_STATE_DEAD ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  in_pcbdetach (struct inpcb*) ; 
 int /*<<< orphan*/  panic (char*,struct socket*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
div_detach(struct socket *so)
{
	struct inpcb *inp;

#ifdef MORE_DICVLOCK_DEBUG
	printf("div_detach: so=0x%llx sopcb=0x%llx lock=0x%llx ref=%x\n",
	    (uint64_t)VM_KERNEL_ADDRPERM(so),
	    (uint64_t)VM_KERNEL_ADDRPERM(so->so_pcb),
	    (uint64_t)VM_KERNEL_ADDRPERM(&(sotoinpcb(so)->inpcb_mtx)),
	    so->so_usecount);
#endif
	inp = sotoinpcb(so);
	if (inp == 0)
		panic("div_detach: so=%p null inp\n", so);
	in_pcbdetach(inp);
	inp->inp_state = INPCB_STATE_DEAD;
	return 0;
}