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
struct TYPE_2__ {int /*<<< orphan*/  proto; } ;
struct xfrm_state {TYPE_1__ id; } ;
struct sk_buff {scalar_t__ data; } ;
struct sadb_msg {int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_seq; scalar_t__ sadb_msg_reserved; scalar_t__ sadb_msg_errno; int /*<<< orphan*/  sadb_msg_satype; int /*<<< orphan*/  sadb_msg_type; int /*<<< orphan*/  sadb_msg_version; } ;
struct km_event {int /*<<< orphan*/  pid; int /*<<< orphan*/  seq; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_ALL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PF_KEY_V2 ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  event2keytype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_broadcast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_proto2satype (int /*<<< orphan*/ ) ; 
 struct sk_buff* pfkey_xfrm_state2msg (struct xfrm_state*) ; 
 int /*<<< orphan*/  xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int key_notify_sa(struct xfrm_state *x, struct km_event *c)
{
	struct sk_buff *skb;
	struct sadb_msg *hdr;

	skb = pfkey_xfrm_state2msg(x);

	if (IS_ERR(skb))
		return PTR_ERR(skb);

	hdr = (struct sadb_msg *) skb->data;
	hdr->sadb_msg_version = PF_KEY_V2;
	hdr->sadb_msg_type = event2keytype(c->event);
	hdr->sadb_msg_satype = pfkey_proto2satype(x->id.proto);
	hdr->sadb_msg_errno = 0;
	hdr->sadb_msg_reserved = 0;
	hdr->sadb_msg_seq = c->seq;
	hdr->sadb_msg_pid = c->pid;

	pfkey_broadcast(skb, GFP_ATOMIC, BROADCAST_ALL, NULL, xs_net(x));

	return 0;
}