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
typedef  scalar_t__ ulong ;
struct sk_buff {int dummy; } ;
struct bio_vec {scalar_t__ bv_len; scalar_t__ bv_offset; int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
skb_fillup(struct sk_buff *skb, struct bio_vec *bv, ulong off, ulong cnt)
{
	int frag = 0;
	ulong fcnt;
loop:
	fcnt = bv->bv_len - (off - bv->bv_offset);
	if (fcnt > cnt)
		fcnt = cnt;
	skb_fill_page_desc(skb, frag++, bv->bv_page, off, fcnt);
	cnt -= fcnt;
	if (cnt <= 0)
		return;
	bv++;
	off = bv->bv_offset;
	goto loop;
}