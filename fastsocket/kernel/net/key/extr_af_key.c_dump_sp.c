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
struct xfrm_policy {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct sadb_msg {int sadb_msg_seq; int /*<<< orphan*/  sadb_msg_pid; scalar_t__ sadb_msg_errno; int /*<<< orphan*/  sadb_msg_satype; int /*<<< orphan*/  sadb_msg_type; int /*<<< orphan*/  sadb_msg_version; } ;
struct TYPE_2__ {struct sk_buff* skb; int /*<<< orphan*/  msg_pid; int /*<<< orphan*/  msg_version; } ;
struct pfkey_sock {TYPE_1__ dump; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_ONE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SADB_SATYPE_UNSPEC ; 
 int /*<<< orphan*/  SADB_X_SPDDUMP ; 
 int /*<<< orphan*/  pfkey_broadcast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_can_dump (int /*<<< orphan*/ *) ; 
 int pfkey_xfrm_policy2msg (struct sk_buff*,struct xfrm_policy*,int) ; 
 struct sk_buff* pfkey_xfrm_policy2msg_prep (struct xfrm_policy*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dump_sp(struct xfrm_policy *xp, int dir, int count, void *ptr)
{
	struct pfkey_sock *pfk = ptr;
	struct sk_buff *out_skb;
	struct sadb_msg *out_hdr;
	int err;

	if (!pfkey_can_dump(&pfk->sk))
		return -ENOBUFS;

	out_skb = pfkey_xfrm_policy2msg_prep(xp);
	if (IS_ERR(out_skb))
		return PTR_ERR(out_skb);

	err = pfkey_xfrm_policy2msg(out_skb, xp, dir);
	if (err < 0)
		return err;

	out_hdr = (struct sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = pfk->dump.msg_version;
	out_hdr->sadb_msg_type = SADB_X_SPDDUMP;
	out_hdr->sadb_msg_satype = SADB_SATYPE_UNSPEC;
	out_hdr->sadb_msg_errno = 0;
	out_hdr->sadb_msg_seq = count + 1;
	out_hdr->sadb_msg_pid = pfk->dump.msg_pid;

	if (pfk->dump.skb)
		pfkey_broadcast(pfk->dump.skb, GFP_ATOMIC, BROADCAST_ONE,
				&pfk->sk, sock_net(&pfk->sk));
	pfk->dump.skb = out_skb;

	return 0;
}