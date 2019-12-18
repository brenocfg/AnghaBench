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
struct sock {scalar_t__ sk_user_data; } ;
struct pppol2tp_session {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ L2TP_SESSION_MAGIC ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static inline struct pppol2tp_session *pppol2tp_sock_to_session(struct sock *sk)
{
	struct pppol2tp_session *session;

	if (sk == NULL)
		return NULL;

	sock_hold(sk);
	session = (struct pppol2tp_session *)(sk->sk_user_data);
	if (session == NULL) {
		sock_put(sk);
		goto out;
	}

	BUG_ON(session->magic != L2TP_SESSION_MAGIC);
out:
	return session;
}