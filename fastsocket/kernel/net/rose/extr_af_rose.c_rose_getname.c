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
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;
struct rose_sock {int dest_ndigis; int source_ndigis; int /*<<< orphan*/ * source_digis; int /*<<< orphan*/  source_call; int /*<<< orphan*/  source_addr; int /*<<< orphan*/ * dest_digis; int /*<<< orphan*/  dest_call; int /*<<< orphan*/  dest_addr; } ;
struct full_sockaddr_rose {int srose_ndigis; int /*<<< orphan*/ * srose_digis; int /*<<< orphan*/  srose_call; int /*<<< orphan*/  srose_addr; void* srose_family; } ;

/* Variables and functions */
 void* AF_ROSE ; 
 int ENOTCONN ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  memset (struct full_sockaddr_rose*,int /*<<< orphan*/ ,int) ; 
 struct rose_sock* rose_sk (struct sock*) ; 

__attribute__((used)) static int rose_getname(struct socket *sock, struct sockaddr *uaddr,
	int *uaddr_len, int peer)
{
	struct full_sockaddr_rose *srose = (struct full_sockaddr_rose *)uaddr;
	struct sock *sk = sock->sk;
	struct rose_sock *rose = rose_sk(sk);
	int n;

	memset(srose, 0, sizeof(*srose));
	if (peer != 0) {
		if (sk->sk_state != TCP_ESTABLISHED)
			return -ENOTCONN;
		srose->srose_family = AF_ROSE;
		srose->srose_addr   = rose->dest_addr;
		srose->srose_call   = rose->dest_call;
		srose->srose_ndigis = rose->dest_ndigis;
		for (n = 0; n < rose->dest_ndigis; n++)
			srose->srose_digis[n] = rose->dest_digis[n];
	} else {
		srose->srose_family = AF_ROSE;
		srose->srose_addr   = rose->source_addr;
		srose->srose_call   = rose->source_call;
		srose->srose_ndigis = rose->source_ndigis;
		for (n = 0; n < rose->source_ndigis; n++)
			srose->srose_digis[n] = rose->source_digis[n];
	}

	*uaddr_len = sizeof(struct full_sockaddr_rose);
	return 0;
}