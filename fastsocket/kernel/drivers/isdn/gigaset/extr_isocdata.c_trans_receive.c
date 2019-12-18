#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__* bas; } ;
struct bc_state {struct sk_buff* skb; TYPE_3__* cs; TYPE_2__ hw; int /*<<< orphan*/  ignore; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  goodbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_STREAM_DUMP ; 
 scalar_t__ HW_HDR_LEN ; 
 scalar_t__ SBUFSIZE ; 
 int TRANSBUFSIZE ; 
 int /*<<< orphan*/  bitrev8 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dump_bytes (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gigaset_rcv_skb (struct sk_buff*,TYPE_3__*,struct bc_state*) ; 
 int /*<<< orphan*/  hdlc_flush (struct bc_state*) ; 
 unsigned char* skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void trans_receive(unsigned char *src, unsigned count,
				 struct bc_state *bcs)
{
	struct sk_buff *skb;
	int dobytes;
	unsigned char *dst;

	if (unlikely(bcs->ignore)) {
		bcs->ignore--;
		hdlc_flush(bcs);
		return;
	}
	if (unlikely((skb = bcs->skb) == NULL)) {
		bcs->skb = skb = dev_alloc_skb(SBUFSIZE + HW_HDR_LEN);
		if (!skb) {
			dev_err(bcs->cs->dev, "could not allocate skb\n");
			return;
		}
		skb_reserve(skb, HW_HDR_LEN);
	}
	bcs->hw.bas->goodbytes += skb->len;
	dobytes = TRANSBUFSIZE - skb->len;
	while (count > 0) {
		dst = skb_put(skb, count < dobytes ? count : dobytes);
		while (count > 0 && dobytes > 0) {
			*dst++ = bitrev8(*src++);
			count--;
			dobytes--;
		}
		if (dobytes == 0) {
			dump_bytes(DEBUG_STREAM_DUMP,
				   "rcv data", skb->data, skb->len);
			gigaset_rcv_skb(skb, bcs->cs, bcs);
			bcs->skb = skb = dev_alloc_skb(SBUFSIZE + HW_HDR_LEN);
			if (!skb) {
				dev_err(bcs->cs->dev,
					"could not allocate skb\n");
				return;
			}
			skb_reserve(bcs->skb, HW_HDR_LEN);
			dobytes = TRANSBUFSIZE;
		}
	}
}