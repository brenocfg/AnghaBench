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
struct nf_nat_seq {int /*<<< orphan*/  offset_before; int /*<<< orphan*/  offset_after; int /*<<< orphan*/  correction_pos; } ;
struct nf_conn_nat {struct nf_nat_seq* seq; } ;
struct nf_conn {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;

/* Variables and functions */
 scalar_t__ after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_nat_seqofs_lock ; 
 struct nf_conn_nat* nfct_nat (struct nf_conn const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

s16 nf_nat_get_offset(const struct nf_conn *ct,
		      enum ip_conntrack_dir dir,
		      u32 seq)
{
	struct nf_conn_nat *nat = nfct_nat(ct);
	struct nf_nat_seq *this_way;
	s16 offset;

	if (!nat)
		return 0;

	this_way = &nat->seq[dir];
	spin_lock_bh(&nf_nat_seqofs_lock);
	offset = after(seq, this_way->correction_pos)
		 ? this_way->offset_after : this_way->offset_before;
	spin_unlock_bh(&nf_nat_seqofs_lock);

	return offset;
}