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
typedef  int /*<<< orphan*/  u32 ;
struct nf_nat_seq {scalar_t__ offset_before; scalar_t__ offset_after; int /*<<< orphan*/  correction_pos; } ;
struct nf_conn_nat {struct nf_nat_seq* seq; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int /*<<< orphan*/  DUMP_OFFSET (struct nf_nat_seq*) ; 
 scalar_t__ before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_nat_seqofs_lock ; 
 struct nf_conn_nat* nfct_nat (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
adjust_tcp_sequence(u32 seq,
		    int sizediff,
		    struct nf_conn *ct,
		    enum ip_conntrack_info ctinfo)
{
	int dir;
	struct nf_nat_seq *this_way, *other_way;
	struct nf_conn_nat *nat = nfct_nat(ct);

	pr_debug("adjust_tcp_sequence: seq = %u, sizediff = %d\n", seq, seq);

	dir = CTINFO2DIR(ctinfo);

	this_way = &nat->seq[dir];
	other_way = &nat->seq[!dir];

	pr_debug("nf_nat_resize_packet: Seq_offset before: ");
	DUMP_OFFSET(this_way);

	spin_lock_bh(&nf_nat_seqofs_lock);

	/* SYN adjust. If it's uninitialized, or this is after last
	 * correction, record it: we don't handle more than one
	 * adjustment in the window, but do deal with common case of a
	 * retransmit */
	if (this_way->offset_before == this_way->offset_after ||
	    before(this_way->correction_pos, seq)) {
		   this_way->correction_pos = seq;
		   this_way->offset_before = this_way->offset_after;
		   this_way->offset_after += sizediff;
	}
	spin_unlock_bh(&nf_nat_seqofs_lock);

	pr_debug("nf_nat_resize_packet: Seq_offset after: ");
	DUMP_OFFSET(this_way);
}