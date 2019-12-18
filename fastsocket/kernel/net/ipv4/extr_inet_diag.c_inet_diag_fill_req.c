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
typedef  void* u32 ;
struct sock {scalar_t__ sk_family; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {int len; } ;
struct request_sock {long expires; int /*<<< orphan*/  retrans; } ;
struct nlmsghdr {int nlmsg_len; int /*<<< orphan*/  nlmsg_flags; int /*<<< orphan*/  nlmsg_type; } ;
struct inet_sock {int /*<<< orphan*/  sport; } ;
struct inet_request_sock {int /*<<< orphan*/  rmt_addr; int /*<<< orphan*/  loc_addr; int /*<<< orphan*/  rmt_port; } ;
struct TYPE_3__ {int /*<<< orphan*/ * idiag_dst; int /*<<< orphan*/ * idiag_src; int /*<<< orphan*/  idiag_dport; int /*<<< orphan*/  idiag_sport; void** idiag_cookie; int /*<<< orphan*/  idiag_if; } ;
struct inet_diag_msg {scalar_t__ idiag_family; int idiag_timer; TYPE_1__ id; scalar_t__ idiag_inode; int /*<<< orphan*/  idiag_uid; scalar_t__ idiag_wqueue; scalar_t__ idiag_rqueue; int /*<<< orphan*/  idiag_expires; int /*<<< orphan*/  idiag_retrans; int /*<<< orphan*/  idiag_state; } ;
struct in6_addr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rmt_addr; int /*<<< orphan*/  loc_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 struct inet_diag_msg* NLMSG_DATA (struct nlmsghdr*) ; 
 struct nlmsghdr* NLMSG_PUT (struct sk_buff*,void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  TCP_SYN_RECV ; 
 TYPE_2__* inet6_rsk (struct request_sock*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct in6_addr*,int /*<<< orphan*/ *) ; 
 long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (long) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_i_uid (struct sock*) ; 

__attribute__((used)) static int inet_diag_fill_req(struct sk_buff *skb, struct sock *sk,
			      struct request_sock *req, u32 pid, u32 seq,
			      const struct nlmsghdr *unlh)
{
	const struct inet_request_sock *ireq = inet_rsk(req);
	struct inet_sock *inet = inet_sk(sk);
	unsigned char *b = skb_tail_pointer(skb);
	struct inet_diag_msg *r;
	struct nlmsghdr *nlh;
	long tmo;

	nlh = NLMSG_PUT(skb, pid, seq, unlh->nlmsg_type, sizeof(*r));
	nlh->nlmsg_flags = NLM_F_MULTI;
	r = NLMSG_DATA(nlh);

	r->idiag_family = sk->sk_family;
	r->idiag_state = TCP_SYN_RECV;
	r->idiag_timer = 1;
	r->idiag_retrans = req->retrans;

	r->id.idiag_if = sk->sk_bound_dev_if;
	r->id.idiag_cookie[0] = (u32)(unsigned long)req;
	r->id.idiag_cookie[1] = (u32)(((unsigned long)req >> 31) >> 1);

	tmo = req->expires - jiffies;
	if (tmo < 0)
		tmo = 0;

	r->id.idiag_sport = inet->sport;
	r->id.idiag_dport = ireq->rmt_port;
	r->id.idiag_src[0] = ireq->loc_addr;
	r->id.idiag_dst[0] = ireq->rmt_addr;
	r->idiag_expires = jiffies_to_msecs(tmo);
	r->idiag_rqueue = 0;
	r->idiag_wqueue = 0;
	r->idiag_uid = sock_i_uid(sk);
	r->idiag_inode = 0;
#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
	if (r->idiag_family == AF_INET6) {
		ipv6_addr_copy((struct in6_addr *)r->id.idiag_src,
			       &inet6_rsk(req)->loc_addr);
		ipv6_addr_copy((struct in6_addr *)r->id.idiag_dst,
			       &inet6_rsk(req)->rmt_addr);
	}
#endif
	nlh->nlmsg_len = skb_tail_pointer(skb) - b;

	return skb->len;

nlmsg_failure:
	nlmsg_trim(skb, b);
	return -1;
}