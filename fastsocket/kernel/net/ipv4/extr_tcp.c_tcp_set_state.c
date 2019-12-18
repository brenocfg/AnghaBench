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
struct sock {int sk_state; int sk_userlocks; TYPE_1__* sk_prot; } ;
struct TYPE_4__ {int /*<<< orphan*/  icsk_bind_hash; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unhash ) (struct sock*) ;} ;

/* Variables and functions */
 int SOCK_BINDPORT_LOCK ; 
 int /*<<< orphan*/  SOCK_DEBUG (struct sock*,char*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TCP_CLOSE 129 
 int TCP_CLOSE_WAIT ; 
 int /*<<< orphan*/  TCP_DEC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TCP_ESTABLISHED 128 
 int /*<<< orphan*/  TCP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_MIB_CURRESTAB ; 
 int /*<<< orphan*/  TCP_MIB_ESTABRESETS ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_put_port (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/ * statename ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

void tcp_set_state(struct sock *sk, int state)
{
	int oldstate = sk->sk_state;

	switch (state) {
	case TCP_ESTABLISHED:
		if (oldstate != TCP_ESTABLISHED)
			TCP_INC_STATS(sock_net(sk), TCP_MIB_CURRESTAB);
		break;

	case TCP_CLOSE:
		if (oldstate == TCP_CLOSE_WAIT || oldstate == TCP_ESTABLISHED)
			TCP_INC_STATS(sock_net(sk), TCP_MIB_ESTABRESETS);

		sk->sk_prot->unhash(sk);
		if (inet_csk(sk)->icsk_bind_hash &&
		    !(sk->sk_userlocks & SOCK_BINDPORT_LOCK))
			inet_put_port(sk);
		/* fall through */
	default:
		if (oldstate == TCP_ESTABLISHED)
			TCP_DEC_STATS(sock_net(sk), TCP_MIB_CURRESTAB);
	}

	/* Change state AFTER socket is unhashed to avoid closed
	 * socket sitting in hash tables.
	 */
	sk->sk_state = state;

#ifdef STATE_TRACE
	SOCK_DEBUG(sk, "TCP sk=%p, State %s -> %s\n", sk, statename[oldstate], statename[state]);
#endif
}