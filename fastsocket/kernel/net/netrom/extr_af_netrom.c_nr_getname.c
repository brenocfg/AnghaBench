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
struct socket {struct sock* sk; } ;
struct sockaddr_ax25 {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;
struct nr_sock {int /*<<< orphan*/  source_addr; int /*<<< orphan*/  dest_addr; int /*<<< orphan*/  user_addr; } ;
struct TYPE_2__ {int sax25_ndigis; int /*<<< orphan*/  sax25_call; void* sax25_family; } ;
struct full_sockaddr_ax25 {TYPE_1__ fsa_ax25; int /*<<< orphan*/ * fsa_digipeater; } ;

/* Variables and functions */
 void* AF_NETROM ; 
 int ENOTCONN ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int nr_getname(struct socket *sock, struct sockaddr *uaddr,
	int *uaddr_len, int peer)
{
	struct full_sockaddr_ax25 *sax = (struct full_sockaddr_ax25 *)uaddr;
	struct sock *sk = sock->sk;
	struct nr_sock *nr = nr_sk(sk);

	lock_sock(sk);
	if (peer != 0) {
		if (sk->sk_state != TCP_ESTABLISHED) {
			release_sock(sk);
			return -ENOTCONN;
		}
		sax->fsa_ax25.sax25_family = AF_NETROM;
		sax->fsa_ax25.sax25_ndigis = 1;
		sax->fsa_ax25.sax25_call   = nr->user_addr;
		memset(sax->fsa_digipeater, 0, sizeof(sax->fsa_digipeater));
		sax->fsa_digipeater[0]     = nr->dest_addr;
		*uaddr_len = sizeof(struct full_sockaddr_ax25);
	} else {
		sax->fsa_ax25.sax25_family = AF_NETROM;
		sax->fsa_ax25.sax25_ndigis = 0;
		sax->fsa_ax25.sax25_call   = nr->source_addr;
		*uaddr_len = sizeof(struct sockaddr_ax25);
	}
	release_sock(sk);

	return 0;
}