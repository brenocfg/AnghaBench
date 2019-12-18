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
struct sockaddr_iucv {int /*<<< orphan*/  siucv_name; int /*<<< orphan*/  siucv_user_id; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_type; } ;
struct iucv_sock {scalar_t__ transport; int /*<<< orphan*/  dst_name; int /*<<< orphan*/  dst_user_id; } ;

/* Variables and functions */
 scalar_t__ AF_IUCV ; 
 int /*<<< orphan*/  AF_IUCV_FLAG_SYN ; 
 scalar_t__ AF_IUCV_TRANS_HIPER ; 
 scalar_t__ AF_IUCV_TRANS_IUCV ; 
 int EBADFD ; 
 int ECONNREFUSED ; 
 int EINVAL ; 
 scalar_t__ IUCV_BOUND ; 
 scalar_t__ IUCV_CLOSED ; 
 scalar_t__ IUCV_CONNECTED ; 
 scalar_t__ IUCV_DISCONN ; 
 scalar_t__ IUCV_OPEN ; 
 int O_NONBLOCK ; 
 scalar_t__ SOCK_SEQPACKET ; 
 scalar_t__ SOCK_STREAM ; 
 int afiucv_path_connect (struct socket*,struct sockaddr*) ; 
 int iucv_send_ctrl (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_sever_path (struct sock*,int /*<<< orphan*/ ) ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int iucv_sock_autobind (struct sock*) ; 
 int /*<<< orphan*/  iucv_sock_in_state (struct sock*,scalar_t__,scalar_t__) ; 
 int iucv_sock_wait (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_sndtimeo (struct sock*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int iucv_sock_connect(struct socket *sock, struct sockaddr *addr,
			     int alen, int flags)
{
	struct sockaddr_iucv *sa = (struct sockaddr_iucv *) addr;
	struct sock *sk = sock->sk;
	struct iucv_sock *iucv = iucv_sk(sk);
	int err;

	if (addr->sa_family != AF_IUCV || alen < sizeof(struct sockaddr_iucv))
		return -EINVAL;

	if (sk->sk_state != IUCV_OPEN && sk->sk_state != IUCV_BOUND)
		return -EBADFD;

	if (sk->sk_state == IUCV_OPEN &&
	    iucv->transport == AF_IUCV_TRANS_HIPER)
		return -EBADFD; /* explicit bind required */

	if (sk->sk_type != SOCK_STREAM && sk->sk_type != SOCK_SEQPACKET)
		return -EINVAL;

	if (sk->sk_state == IUCV_OPEN) {
		err = iucv_sock_autobind(sk);
		if (unlikely(err))
			return err;
	}

	lock_sock(sk);

	/* Set the destination information */
	memcpy(iucv->dst_user_id, sa->siucv_user_id, 8);
	memcpy(iucv->dst_name, sa->siucv_name, 8);

	if (iucv->transport == AF_IUCV_TRANS_HIPER)
		err = iucv_send_ctrl(sk, AF_IUCV_FLAG_SYN);
	else
		err = afiucv_path_connect(sock, addr);
	if (err)
		goto done;

	if (sk->sk_state != IUCV_CONNECTED)
		err = iucv_sock_wait(sk, iucv_sock_in_state(sk, IUCV_CONNECTED,
							    IUCV_DISCONN),
				     sock_sndtimeo(sk, flags & O_NONBLOCK));

	if (sk->sk_state == IUCV_DISCONN || sk->sk_state == IUCV_CLOSED)
		err = -ECONNREFUSED;

	if (err && iucv->transport == AF_IUCV_TRANS_IUCV)
		iucv_sever_path(sk, 0);

done:
	release_sock(sk);
	return err;
}