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
typedef  int /*<<< orphan*/  uint64_t ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_msg {int sadb_msg_satype; int sadb_msg_len; scalar_t__ sadb_msg_errno; } ;
struct pfkey_sock {int promisc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_ALL ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  pfkey_broadcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pfkey_sock* pfkey_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int pfkey_promisc(struct sock *sk, struct sk_buff *skb, struct sadb_msg *hdr, void **ext_hdrs)
{
	struct pfkey_sock *pfk = pfkey_sk(sk);
	int satype = hdr->sadb_msg_satype;

	if (hdr->sadb_msg_len == (sizeof(*hdr) / sizeof(uint64_t))) {
		/* XXX we mangle packet... */
		hdr->sadb_msg_errno = 0;
		if (satype != 0 && satype != 1)
			return -EINVAL;
		pfk->promisc = satype;
	}
	pfkey_broadcast(skb_clone(skb, GFP_KERNEL), GFP_KERNEL, BROADCAST_ALL, NULL, sock_net(sk));
	return 0;
}