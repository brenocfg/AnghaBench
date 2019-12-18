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
struct tcphdr {void* seq; void* ack_seq; int /*<<< orphan*/  check; } ;
struct sk_buff {scalar_t__ data; } ;
struct nf_nat_seq {scalar_t__ offset_before; scalar_t__ offset_after; int /*<<< orphan*/  correction_pos; } ;
struct nf_conn_nat {struct nf_nat_seq* seq; } ;
struct nf_conn {int dummy; } ;
typedef  scalar_t__ s16 ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  void* __be32 ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 scalar_t__ after (scalar_t__,int /*<<< orphan*/ ) ; 
 void* htonl (scalar_t__) ; 
 int /*<<< orphan*/  inet_proto_csum_replace4 (int /*<<< orphan*/ *,struct sk_buff*,void*,void*,int /*<<< orphan*/ ) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int nf_nat_sack_adjust (struct sk_buff*,struct tcphdr*,struct nf_conn*,int) ; 
 struct nf_conn_nat* nfct_nat (struct nf_conn*) ; 
 scalar_t__ ntohl (void*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int) ; 

int
nf_nat_seq_adjust(struct sk_buff *skb,
		  struct nf_conn *ct,
		  enum ip_conntrack_info ctinfo)
{
	struct tcphdr *tcph;
	int dir;
	__be32 newseq, newack;
	s16 seqoff, ackoff;
	struct nf_conn_nat *nat = nfct_nat(ct);
	struct nf_nat_seq *this_way, *other_way;

	dir = CTINFO2DIR(ctinfo);

	this_way = &nat->seq[dir];
	other_way = &nat->seq[!dir];

	if (!skb_make_writable(skb, ip_hdrlen(skb) + sizeof(*tcph)))
		return 0;

	tcph = (void *)skb->data + ip_hdrlen(skb);
	if (after(ntohl(tcph->seq), this_way->correction_pos))
		seqoff = this_way->offset_after;
	else
		seqoff = this_way->offset_before;

	if (after(ntohl(tcph->ack_seq) - other_way->offset_before,
		  other_way->correction_pos))
		ackoff = other_way->offset_after;
	else
		ackoff = other_way->offset_before;

	newseq = htonl(ntohl(tcph->seq) + seqoff);
	newack = htonl(ntohl(tcph->ack_seq) - ackoff);

	inet_proto_csum_replace4(&tcph->check, skb, tcph->seq, newseq, 0);
	inet_proto_csum_replace4(&tcph->check, skb, tcph->ack_seq, newack, 0);

	pr_debug("Adjusting sequence number from %u->%u, ack from %u->%u\n",
		 ntohl(tcph->seq), ntohl(newseq), ntohl(tcph->ack_seq),
		 ntohl(newack));

	tcph->seq = newseq;
	tcph->ack_seq = newack;

	return nf_nat_sack_adjust(skb, tcph, ct, ctinfo);
}