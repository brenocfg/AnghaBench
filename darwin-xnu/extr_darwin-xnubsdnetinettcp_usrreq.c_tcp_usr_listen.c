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
struct tcpcb {int /*<<< orphan*/  t_state; } ;
struct socket {int dummy; } ;
struct proc {int dummy; } ;
struct inpcb {scalar_t__ inp_lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMMON_START () ; 
 int /*<<< orphan*/  PRU_LISTEN ; 
 int /*<<< orphan*/  TCPS_LISTEN ; 
 int in_pcbbind (struct inpcb*,int /*<<< orphan*/ *,struct proc*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
tcp_usr_listen(struct socket *so, struct proc *p)
{
	int error = 0;
	struct inpcb *inp = sotoinpcb(so);
	struct tcpcb *tp;

	COMMON_START();
	if (inp->inp_lport == 0)
		error = in_pcbbind(inp, NULL, p);
	if (error == 0)
		tp->t_state = TCPS_LISTEN;
	COMMON_END(PRU_LISTEN);
}