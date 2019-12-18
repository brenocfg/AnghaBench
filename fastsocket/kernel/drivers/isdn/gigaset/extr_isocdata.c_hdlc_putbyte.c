#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* bas; } ;
struct bc_state {TYPE_4__* skb; TYPE_3__ hw; TYPE_1__* cs; int /*<<< orphan*/  fcs; } ;
struct TYPE_9__ {scalar_t__ len; } ;
struct TYPE_7__ {int /*<<< orphan*/  giants; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SBUFSIZE ; 
 unsigned char* __skb_put (TYPE_4__*,int) ; 
 int /*<<< orphan*/  crc_ccitt_byte (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void hdlc_putbyte(unsigned char c, struct bc_state *bcs)
{
	bcs->fcs = crc_ccitt_byte(bcs->fcs, c);
	if (unlikely(bcs->skb == NULL)) {
		/* skipping */
		return;
	}
	if (unlikely(bcs->skb->len == SBUFSIZE)) {
		dev_warn(bcs->cs->dev, "received oversized packet discarded\n");
		bcs->hw.bas->giants++;
		dev_kfree_skb_any(bcs->skb);
		bcs->skb = NULL;
		return;
	}
	*__skb_put(bcs->skb, 1) = c;
}