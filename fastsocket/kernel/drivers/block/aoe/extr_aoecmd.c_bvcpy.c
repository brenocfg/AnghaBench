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
typedef  long ulong ;
struct sk_buff {int dummy; } ;
struct bio_vec {long bv_len; long bv_offset; int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 char* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int,char*,long) ; 

__attribute__((used)) static void
bvcpy(struct bio_vec *bv, ulong off, struct sk_buff *skb, long cnt)
{
	ulong fcnt;
	char *p;
	int soff = 0;
loop:
	fcnt = bv->bv_len - (off - bv->bv_offset);
	if (fcnt > cnt)
		fcnt = cnt;
	p = page_address(bv->bv_page) + off;
	skb_copy_bits(skb, soff, p, fcnt);
	soff += fcnt;
	cnt -= fcnt;
	if (cnt <= 0)
		return;
	bv++;
	off = bv->bv_offset;
	goto loop;
}