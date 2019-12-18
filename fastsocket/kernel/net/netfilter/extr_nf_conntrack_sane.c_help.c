#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int doff; } ;
struct sk_buff {unsigned int len; } ;
struct sane_request {scalar_t__ RPC_code; } ;
struct sane_reply_net_start {scalar_t__ status; scalar_t__ zero; int /*<<< orphan*/  port; } ;
struct nf_ct_sane_master {scalar_t__ state; } ;
struct TYPE_9__ {int /*<<< orphan*/  u3; } ;
struct TYPE_8__ {int /*<<< orphan*/  u3; } ;
struct nf_conntrack_tuple {TYPE_4__ dst; TYPE_3__ src; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  tuple; } ;
struct nf_conn {TYPE_2__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  _tcph ;
struct TYPE_6__ {struct nf_ct_sane_master ct_sane_info; } ;
struct TYPE_10__ {TYPE_1__ help; } ;
struct TYPE_7__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int CTINFO2DIR (int) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int IP_CT_DIR_ORIGINAL ; 
 int IP_CT_ESTABLISHED ; 
 int IP_CT_IS_REPLY ; 
 int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_CT_EXPECT_CLASS_DEFAULT ; 
 int NF_DROP ; 
 int /*<<< orphan*/  SANE_NET_START ; 
 void* SANE_STATE_NORMAL ; 
 scalar_t__ SANE_STATE_START_REQUESTED ; 
 int /*<<< orphan*/  SANE_STATUS_SUCCESS ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_dump_tuple (int /*<<< orphan*/ *) ; 
 struct nf_conntrack_expect* nf_ct_expect_alloc (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_expect_init (struct nf_conntrack_expect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_expect_put (struct nf_conntrack_expect*) ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_sane_lock ; 
 TYPE_5__* nfct_help (struct nf_conn*) ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct tcphdr* sane_buffer ; 
 void* skb_header_pointer (struct sk_buff*,unsigned int,unsigned int,struct tcphdr*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int help(struct sk_buff *skb,
		unsigned int protoff,
		struct nf_conn *ct,
		enum ip_conntrack_info ctinfo)
{
	unsigned int dataoff, datalen;
	const struct tcphdr *th;
	struct tcphdr _tcph;
	void *sb_ptr;
	int ret = NF_ACCEPT;
	int dir = CTINFO2DIR(ctinfo);
	struct nf_ct_sane_master *ct_sane_info;
	struct nf_conntrack_expect *exp;
	struct nf_conntrack_tuple *tuple;
	struct sane_request *req;
	struct sane_reply_net_start *reply;

	ct_sane_info = &nfct_help(ct)->help.ct_sane_info;
	/* Until there's been traffic both ways, don't look in packets. */
	if (ctinfo != IP_CT_ESTABLISHED &&
	    ctinfo != IP_CT_ESTABLISHED+IP_CT_IS_REPLY)
		return NF_ACCEPT;

	/* Not a full tcp header? */
	th = skb_header_pointer(skb, protoff, sizeof(_tcph), &_tcph);
	if (th == NULL)
		return NF_ACCEPT;

	/* No data? */
	dataoff = protoff + th->doff * 4;
	if (dataoff >= skb->len)
		return NF_ACCEPT;

	datalen = skb->len - dataoff;

	spin_lock_bh(&nf_sane_lock);
	sb_ptr = skb_header_pointer(skb, dataoff, datalen, sane_buffer);
	BUG_ON(sb_ptr == NULL);

	if (dir == IP_CT_DIR_ORIGINAL) {
		if (datalen != sizeof(struct sane_request))
			goto out;

		req = sb_ptr;
		if (req->RPC_code != htonl(SANE_NET_START)) {
			/* Not an interesting command */
			ct_sane_info->state = SANE_STATE_NORMAL;
			goto out;
		}

		/* We're interested in the next reply */
		ct_sane_info->state = SANE_STATE_START_REQUESTED;
		goto out;
	}

	/* Is it a reply to an uninteresting command? */
	if (ct_sane_info->state != SANE_STATE_START_REQUESTED)
		goto out;

	/* It's a reply to SANE_NET_START. */
	ct_sane_info->state = SANE_STATE_NORMAL;

	if (datalen < sizeof(struct sane_reply_net_start)) {
		pr_debug("nf_ct_sane: NET_START reply too short\n");
		goto out;
	}

	reply = sb_ptr;
	if (reply->status != htonl(SANE_STATUS_SUCCESS)) {
		/* saned refused the command */
		pr_debug("nf_ct_sane: unsuccessful SANE_STATUS = %u\n",
			 ntohl(reply->status));
		goto out;
	}

	/* Invalid saned reply? Ignore it. */
	if (reply->zero != 0)
		goto out;

	exp = nf_ct_expect_alloc(ct);
	if (exp == NULL) {
		ret = NF_DROP;
		goto out;
	}

	tuple = &ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &tuple->src.u3, &tuple->dst.u3,
			  IPPROTO_TCP, NULL, &reply->port);

	pr_debug("nf_ct_sane: expect: ");
	nf_ct_dump_tuple(&exp->tuple);

	/* Can't expect this?  Best to drop packet now. */
	if (nf_ct_expect_related(exp) != 0)
		ret = NF_DROP;

	nf_ct_expect_put(exp);

out:
	spin_unlock_bh(&nf_sane_lock);
	return ret;
}