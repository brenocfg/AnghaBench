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
struct sadb_msg {int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_seq; scalar_t__ sadb_msg_errno; int /*<<< orphan*/  sadb_msg_type; int /*<<< orphan*/  sadb_msg_version; } ;
struct TYPE_2__ {scalar_t__ byid; } ;
struct km_event {scalar_t__ event; int /*<<< orphan*/  pid; int /*<<< orphan*/  seq; TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_ALL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PF_KEY_V2 ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SADB_X_SPDDELETE2 ; 
 scalar_t__ XFRM_MSG_DELPOLICY ; 
 int /*<<< orphan*/  event2poltype (scalar_t__) ; 
 int /*<<< orphan*/  pfkey_broadcast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pfkey_xfrm_policy2msg (struct sk_buff*,struct xfrm_policy*,int) ; 
 struct sk_buff* pfkey_xfrm_policy2msg_prep (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static int key_notify_policy(struct xfrm_policy *xp, int dir, struct km_event *c)
{
	struct sk_buff *out_skb;
	struct sadb_msg *out_hdr;
	int err;

	out_skb = pfkey_xfrm_policy2msg_prep(xp);
	if (IS_ERR(out_skb)) {
		err = PTR_ERR(out_skb);
		goto out;
	}
	err = pfkey_xfrm_policy2msg(out_skb, xp, dir);
	if (err < 0)
		return err;

	out_hdr = (struct sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = PF_KEY_V2;

	if (c->data.byid && c->event == XFRM_MSG_DELPOLICY)
		out_hdr->sadb_msg_type = SADB_X_SPDDELETE2;
	else
		out_hdr->sadb_msg_type = event2poltype(c->event);
	out_hdr->sadb_msg_errno = 0;
	out_hdr->sadb_msg_seq = c->seq;
	out_hdr->sadb_msg_pid = c->pid;
	pfkey_broadcast(out_skb, GFP_ATOMIC, BROADCAST_ALL, NULL, xp_net(xp));
out:
	return 0;

}