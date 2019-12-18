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
typedef  void* u8 ;
struct sockaddr_pn {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct pnpipehdr {void** data; int /*<<< orphan*/  pipe_handle; int /*<<< orphan*/  message_id; int /*<<< orphan*/  utid; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_PHONET_HEADER ; 
 scalar_t__ MAX_PNPIPE_HEADER ; 
 void* PAD ; 
 int /*<<< orphan*/  PNS_PEP_CTRL_RESP ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pn_skb_get_src_sockaddr (struct sk_buff*,struct sockaddr_pn*) ; 
 int pn_skb_send (struct sock*,struct sk_buff*,struct sockaddr_pn*) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 

__attribute__((used)) static int pep_ctrlreq_error(struct sock *sk, struct sk_buff *oskb, u8 code,
				gfp_t priority)
{
	const struct pnpipehdr *oph = pnp_hdr(oskb);
	struct sk_buff *skb;
	struct pnpipehdr *ph;
	struct sockaddr_pn dst;

	skb = alloc_skb(MAX_PNPIPE_HEADER + 4, priority);
	if (!skb)
		return -ENOMEM;
	skb_set_owner_w(skb, sk);

	skb_reserve(skb, MAX_PHONET_HEADER);
	ph = (struct pnpipehdr *)skb_put(skb, sizeof(*ph) + 4);

	ph->utid = oph->utid;
	ph->message_id = PNS_PEP_CTRL_RESP;
	ph->pipe_handle = oph->pipe_handle;
	ph->data[0] = oph->data[1]; /* CTRL id */
	ph->data[1] = oph->data[0]; /* PEP type */
	ph->data[2] = code; /* error code, at an usual offset */
	ph->data[3] = PAD;
	ph->data[4] = PAD;

	pn_skb_get_src_sockaddr(oskb, &dst);
	return pn_skb_send(sk, skb, &dst);
}