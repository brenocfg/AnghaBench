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
struct socket {int dummy; } ;
struct sadb_msghdr {TYPE_1__* msg; } ;
struct sadb_msg {int dummy; } ;
struct mbuf {int dummy; } ;
struct keycb {int kp_promisc; } ;
struct TYPE_2__ {int sadb_msg_satype; scalar_t__ sadb_msg_errno; int /*<<< orphan*/  sadb_msg_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  KEY_SENDUP_ALL ; 
 int /*<<< orphan*/  PFKEY_ALIGN8 (int) ; 
 int PFKEY_UNUNIT64 (int /*<<< orphan*/ ) ; 
 int key_senderror (struct socket*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int key_sendup_mbuf (struct socket*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 scalar_t__ sotorawcb (struct socket*) ; 

__attribute__((used)) static int
key_promisc(
			struct socket *so,
			struct mbuf *m,
			const struct sadb_msghdr *mhp)
{
	int olen;
	
	/* sanity check */
	if (so == NULL || m == NULL || mhp == NULL || mhp->msg == NULL)
		panic("key_promisc: NULL pointer is passed.\n");
	
	olen = PFKEY_UNUNIT64(mhp->msg->sadb_msg_len);
	
	if (olen < sizeof(struct sadb_msg)) {
#if 1
		return key_senderror(so, m, EINVAL);
#else
		m_freem(m);
		return 0;
#endif
	} else if (olen == sizeof(struct sadb_msg)) {
		/* enable/disable promisc mode */
		struct keycb *kp;
		
		socket_lock(so, 1);
		if ((kp = (struct keycb *)sotorawcb(so)) == NULL)
			return key_senderror(so, m, EINVAL);
		mhp->msg->sadb_msg_errno = 0;
		switch (mhp->msg->sadb_msg_satype) {
			case 0:
			case 1:
				kp->kp_promisc = mhp->msg->sadb_msg_satype;
				break;
			default:
				socket_unlock(so, 1);
				return key_senderror(so, m, EINVAL);
		}
		socket_unlock(so, 1);
		
		/* send the original message back to everyone */
		mhp->msg->sadb_msg_errno = 0;
		return key_sendup_mbuf(so, m, KEY_SENDUP_ALL);
	} else {
		/* send packet as is */
		
		m_adj(m, PFKEY_ALIGN8(sizeof(struct sadb_msg)));
		
		/* TODO: if sadb_msg_seq is specified, send to specific pid */
		return key_sendup_mbuf(so, m, KEY_SENDUP_ALL);
	}
}