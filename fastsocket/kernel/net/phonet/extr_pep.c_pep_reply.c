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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct pnpipehdr {int /*<<< orphan*/  error_code; int /*<<< orphan*/  pipe_handle; scalar_t__ message_id; int /*<<< orphan*/  utid; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MAX_PNPIPE_HEADER ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_srv ; 
 int pn_skb_send (struct sock*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 void* pnp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void const*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 

__attribute__((used)) static int pep_reply(struct sock *sk, struct sk_buff *oskb,
			u8 code, const void *data, int len, gfp_t priority)
{
	const struct pnpipehdr *oph = pnp_hdr(oskb);
	struct pnpipehdr *ph;
	struct sk_buff *skb;

	skb = alloc_skb(MAX_PNPIPE_HEADER + len, priority);
	if (!skb)
		return -ENOMEM;
	skb_set_owner_w(skb, sk);

	skb_reserve(skb, MAX_PNPIPE_HEADER);
	__skb_put(skb, len);
	skb_copy_to_linear_data(skb, data, len);
	__skb_push(skb, sizeof(*ph));
	skb_reset_transport_header(skb);
	ph = pnp_hdr(skb);
	ph->utid = oph->utid;
	ph->message_id = oph->message_id + 1; /* REQ -> RESP */
	ph->pipe_handle = oph->pipe_handle;
	ph->error_code = code;

	return pn_skb_send(sk, skb, &pipe_srv);
}