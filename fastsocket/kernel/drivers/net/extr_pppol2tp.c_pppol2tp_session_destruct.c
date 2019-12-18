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
struct sock {struct pppol2tp_session* sk_user_data; } ;
struct pppol2tp_tunnel {scalar_t__ magic; int /*<<< orphan*/  hlist_lock; } ;
struct TYPE_2__ {scalar_t__ s_session; } ;
struct pppol2tp_session {scalar_t__ magic; int /*<<< orphan*/ * tunnel_sock; struct pppol2tp_tunnel* tunnel; int /*<<< orphan*/  hlist; TYPE_1__ tunnel_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ L2TP_SESSION_MAGIC ; 
 scalar_t__ L2TP_TUNNEL_MAGIC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pppol2tp_session*) ; 
 int /*<<< orphan*/  pppol2tp_session_count ; 
 int /*<<< orphan*/  pppol2tp_tunnel_dec_refcount (struct pppol2tp_tunnel*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pppol2tp_session_destruct(struct sock *sk)
{
	struct pppol2tp_session *session = NULL;

	if (sk->sk_user_data != NULL) {
		struct pppol2tp_tunnel *tunnel;

		session = sk->sk_user_data;
		if (session == NULL)
			goto out;

		BUG_ON(session->magic != L2TP_SESSION_MAGIC);

		/* Don't use pppol2tp_sock_to_tunnel() here to
		 * get the tunnel context because the tunnel
		 * socket might have already been closed (its
		 * sk->sk_user_data will be NULL) so use the
		 * session's private tunnel ptr instead.
		 */
		tunnel = session->tunnel;
		if (tunnel != NULL) {
			BUG_ON(tunnel->magic != L2TP_TUNNEL_MAGIC);

			/* If session_id is zero, this is a null
			 * session context, which was created for a
			 * socket that is being used only to manage
			 * tunnels.
			 */
			if (session->tunnel_addr.s_session != 0) {
				/* Delete the session socket from the
				 * hash
				 */
				write_lock_bh(&tunnel->hlist_lock);
				hlist_del_init(&session->hlist);
				write_unlock_bh(&tunnel->hlist_lock);

				atomic_dec(&pppol2tp_session_count);
			}

			/* This will delete the tunnel context if this
			 * is the last session on the tunnel.
			 */
			session->tunnel = NULL;
			session->tunnel_sock = NULL;
			pppol2tp_tunnel_dec_refcount(tunnel);
		}
	}

	kfree(session);
out:
	return;
}