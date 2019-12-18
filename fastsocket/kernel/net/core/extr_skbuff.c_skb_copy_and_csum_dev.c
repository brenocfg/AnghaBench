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
struct sk_buff {scalar_t__ ip_summed; long csum_start; long len; long csum_offset; } ;
typedef  scalar_t__ __wsum ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  csum_fold (scalar_t__) ; 
 scalar_t__ skb_copy_and_csum_bits (struct sk_buff const*,long,int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff const*,int /*<<< orphan*/ *,long) ; 
 long skb_headlen (struct sk_buff const*) ; 
 long skb_headroom (struct sk_buff const*) ; 

void skb_copy_and_csum_dev(const struct sk_buff *skb, u8 *to)
{
	__wsum csum;
	long csstart;

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		csstart = skb->csum_start - skb_headroom(skb);
	else
		csstart = skb_headlen(skb);

	BUG_ON(csstart > skb_headlen(skb));

	skb_copy_from_linear_data(skb, to, csstart);

	csum = 0;
	if (csstart != skb->len)
		csum = skb_copy_and_csum_bits(skb, csstart, to + csstart,
					      skb->len - csstart, 0);

	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		long csstuff = csstart + skb->csum_offset;

		*((__sum16 *)(to + csstuff)) = csum_fold(csum);
	}
}