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
struct socket {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRU_PRECONNECT ; 
 scalar_t__ necp_socket_should_use_flow_divert (struct inpcb*) ; 
 int /*<<< orphan*/  soclearfastopen (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  sototcpcb (struct socket*) ; 
 int tcp_output (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tcp_usr_preconnect(struct socket *so)
{
	struct inpcb *inp = sotoinpcb(so);
	int error = 0;

#if NECP
	if (necp_socket_should_use_flow_divert(inp)) {
		/* May happen, if in tcp_usr_connect we did not had a chance
		 * to set the usrreqs (due to some error). So, let's get out
		 * of here.
		 */
		goto out;
	}
#endif /* NECP */

	error = tcp_output(sototcpcb(so));

	soclearfastopen(so);

	COMMON_END(PRU_PRECONNECT);
}