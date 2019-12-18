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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct pnpipehdr {void** data; int /*<<< orphan*/  pep_type; int /*<<< orphan*/  pipe_handle; int /*<<< orphan*/  message_id; scalar_t__ utid; } ;
struct pep_sock {int /*<<< orphan*/  pipe_handle; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MAX_PNPIPE_HEADER ; 
 void* PAD ; 
 int /*<<< orphan*/  PNS_PEP_STATUS_IND ; 
 int /*<<< orphan*/  PN_PEP_TYPE_COMMON ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  pipe_srv ; 
 int pn_skb_send (struct sock*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 

__attribute__((used)) static int pipe_snd_status(struct sock *sk, u8 type, u8 status, gfp_t priority)
{
	struct pep_sock *pn = pep_sk(sk);
	struct pnpipehdr *ph;
	struct sk_buff *skb;

	skb = alloc_skb(MAX_PNPIPE_HEADER + 4, priority);
	if (!skb)
		return -ENOMEM;
	skb_set_owner_w(skb, sk);

	skb_reserve(skb, MAX_PNPIPE_HEADER + 4);
	__skb_push(skb, sizeof(*ph) + 4);
	skb_reset_transport_header(skb);
	ph = pnp_hdr(skb);
	ph->utid = 0;
	ph->message_id = PNS_PEP_STATUS_IND;
	ph->pipe_handle = pn->pipe_handle;
	ph->pep_type = PN_PEP_TYPE_COMMON;
	ph->data[1] = type;
	ph->data[2] = PAD;
	ph->data[3] = PAD;
	ph->data[4] = status;

	return pn_skb_send(sk, skb, &pipe_srv);
}