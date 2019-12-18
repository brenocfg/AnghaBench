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
struct TYPE_3__ {int /*<<< orphan*/  proto; } ;
struct xfrm_state {TYPE_1__ id; } ;
struct sk_buff {scalar_t__ data; } ;
struct sadb_msg {int sadb_msg_seq; int /*<<< orphan*/  sadb_msg_pid; scalar_t__ sadb_msg_reserved; scalar_t__ sadb_msg_errno; int /*<<< orphan*/  sadb_msg_satype; int /*<<< orphan*/  sadb_msg_type; int /*<<< orphan*/  sadb_msg_version; } ;
struct TYPE_4__ {struct sk_buff* skb; int /*<<< orphan*/  msg_pid; int /*<<< orphan*/  msg_version; } ;
struct pfkey_sock {TYPE_2__ dump; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_ONE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SADB_DUMP ; 
 int /*<<< orphan*/  pfkey_broadcast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_can_dump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfkey_proto2satype (int /*<<< orphan*/ ) ; 
 struct sk_buff* pfkey_xfrm_state2msg (struct xfrm_state*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dump_sa(struct xfrm_state *x, int count, void *ptr)
{
	struct pfkey_sock *pfk = ptr;
	struct sk_buff *out_skb;
	struct sadb_msg *out_hdr;

	if (!pfkey_can_dump(&pfk->sk))
		return -ENOBUFS;

	out_skb = pfkey_xfrm_state2msg(x);
	if (IS_ERR(out_skb))
		return PTR_ERR(out_skb);

	out_hdr = (struct sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = pfk->dump.msg_version;
	out_hdr->sadb_msg_type = SADB_DUMP;
	out_hdr->sadb_msg_satype = pfkey_proto2satype(x->id.proto);
	out_hdr->sadb_msg_errno = 0;
	out_hdr->sadb_msg_reserved = 0;
	out_hdr->sadb_msg_seq = count + 1;
	out_hdr->sadb_msg_pid = pfk->dump.msg_pid;

	if (pfk->dump.skb)
		pfkey_broadcast(pfk->dump.skb, GFP_ATOMIC, BROADCAST_ONE,
				&pfk->sk, sock_net(&pfk->sk));
	pfk->dump.skb = out_skb;

	return 0;
}