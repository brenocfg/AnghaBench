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
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {scalar_t__ all; } ;
struct ipv6_pinfo {TYPE_1__ rxopt; } ;

/* Variables and functions */
 scalar_t__ DCCP_LISTEN ; 
 scalar_t__ DCCP_OPEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 scalar_t__ dccp_child_process (struct sock*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_hdr (struct sk_buff*) ; 
 scalar_t__ dccp_rcv_established (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dccp_rcv_state_process (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dccp_v4_do_rcv (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_v6_ctl_send_reset (struct sock*,struct sk_buff*) ; 
 struct sock* dccp_v6_hnd_req (struct sock*,struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ sk_filter (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_v6_do_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sk_buff *opt_skb = NULL;

	/* Imagine: socket is IPv6. IPv4 packet arrives,
	   goes to IPv4 receive handler and backlogged.
	   From backlog it always goes here. Kerboom...
	   Fortunately, dccp_rcv_established and rcv_established
	   handle them correctly, but it is not case with
	   dccp_v6_hnd_req and dccp_v6_ctl_send_reset().   --ANK
	 */

	if (skb->protocol == htons(ETH_P_IP))
		return dccp_v4_do_rcv(sk, skb);

	if (sk_filter(sk, skb))
		goto discard;

	/*
	 * socket locking is here for SMP purposes as backlog rcv is currently
	 * called with bh processing disabled.
	 */

	/* Do Stevens' IPV6_PKTOPTIONS.

	   Yes, guys, it is the only place in our code, where we
	   may make it not affecting IPv4.
	   The rest of code is protocol independent,
	   and I do not like idea to uglify IPv4.

	   Actually, all the idea behind IPV6_PKTOPTIONS
	   looks not very well thought. For now we latch
	   options, received in the last packet, enqueued
	   by tcp. Feel free to propose better solution.
					       --ANK (980728)
	 */
	if (np->rxopt.all)
	/*
	 * FIXME: Add handling of IPV6_PKTOPTIONS skb. See the comments below
	 *        (wrt ipv6_pktopions) and net/ipv6/tcp_ipv6.c for an example.
	 */
		opt_skb = skb_clone(skb, GFP_ATOMIC);

	if (sk->sk_state == DCCP_OPEN) { /* Fast path */
		if (dccp_rcv_established(sk, skb, dccp_hdr(skb), skb->len))
			goto reset;
		if (opt_skb) {
			/* XXX This is where we would goto ipv6_pktoptions. */
			__kfree_skb(opt_skb);
		}
		return 0;
	}

	/*
	 *  Step 3: Process LISTEN state
	 *     If S.state == LISTEN,
	 *	 If P.type == Request or P contains a valid Init Cookie option,
	 *	      (* Must scan the packet's options to check for Init
	 *		 Cookies.  Only Init Cookies are processed here,
	 *		 however; other options are processed in Step 8.  This
	 *		 scan need only be performed if the endpoint uses Init
	 *		 Cookies *)
	 *	      (* Generate a new socket and switch to that socket *)
	 *	      Set S := new socket for this port pair
	 *	      S.state = RESPOND
	 *	      Choose S.ISS (initial seqno) or set from Init Cookies
	 *	      Initialize S.GAR := S.ISS
	 *	      Set S.ISR, S.GSR, S.SWL, S.SWH from packet or Init Cookies
	 *	      Continue with S.state == RESPOND
	 *	      (* A Response packet will be generated in Step 11 *)
	 *	 Otherwise,
	 *	      Generate Reset(No Connection) unless P.type == Reset
	 *	      Drop packet and return
	 *
	 * NOTE: the check for the packet types is done in
	 *	 dccp_rcv_state_process
	 */
	if (sk->sk_state == DCCP_LISTEN) {
		struct sock *nsk = dccp_v6_hnd_req(sk, skb);

		if (nsk == NULL)
			goto discard;
		/*
		 * Queue it on the new socket if the new socket is active,
		 * otherwise we just shortcircuit this and continue with
		 * the new socket..
		 */
		if (nsk != sk) {
			if (dccp_child_process(sk, nsk, skb))
				goto reset;
			if (opt_skb != NULL)
				__kfree_skb(opt_skb);
			return 0;
		}
	}

	if (dccp_rcv_state_process(sk, skb, dccp_hdr(skb), skb->len))
		goto reset;
	if (opt_skb) {
		/* XXX This is where we would goto ipv6_pktoptions. */
		__kfree_skb(opt_skb);
	}
	return 0;

reset:
	dccp_v6_ctl_send_reset(sk, skb);
discard:
	if (opt_skb != NULL)
		__kfree_skb(opt_skb);
	kfree_skb(skb);
	return 0;
}