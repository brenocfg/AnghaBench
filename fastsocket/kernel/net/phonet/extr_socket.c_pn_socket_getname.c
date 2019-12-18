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
struct socket {struct sock* sk; } ;
struct sockaddr_pn {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct sock {int dummy; } ;
struct pn_sock {int /*<<< orphan*/  sobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PHONET ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 struct pn_sock* pn_sk (struct sock*) ; 
 int /*<<< orphan*/  pn_sockaddr_set_object (struct sockaddr_pn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pn_socket_getname(struct socket *sock, struct sockaddr *addr,
				int *sockaddr_len, int peer)
{
	struct sock *sk = sock->sk;
	struct pn_sock *pn = pn_sk(sk);

	memset(addr, 0, sizeof(struct sockaddr_pn));
	addr->sa_family = AF_PHONET;
	if (!peer) /* Race with bind() here is userland's problem. */
		pn_sockaddr_set_object((struct sockaddr_pn *)addr,
					pn->sobject);

	*sockaddr_len = sizeof(struct sockaddr_pn);
	return 0;
}