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
struct TYPE_5__ {TYPE_1__* bas; } ;
struct bc_state {int /*<<< orphan*/  fcs; TYPE_3__* cs; int /*<<< orphan*/ * skb; TYPE_2__ hw; int /*<<< orphan*/  ignore; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  alignerrs; } ;

/* Variables and functions */
 scalar_t__ HW_HDR_LEN ; 
 int /*<<< orphan*/  PPP_INITFCS ; 
 scalar_t__ SBUFSIZE ; 
 int /*<<< orphan*/ * dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  gigaset_rcv_error (int /*<<< orphan*/ *,TYPE_3__*,struct bc_state*) ; 
 int /*<<< orphan*/  hdlc_flush (struct bc_state*) ; 
 int /*<<< orphan*/  skb_reserve (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hdlc_frag(struct bc_state *bcs, unsigned inbits)
{
	if (unlikely(bcs->ignore)) {
		bcs->ignore--;
		hdlc_flush(bcs);
		return;
	}

	dev_notice(bcs->cs->dev, "received partial byte (%d bits)\n", inbits);
	bcs->hw.bas->alignerrs++;
	gigaset_rcv_error(bcs->skb, bcs->cs, bcs);

	if ((bcs->skb = dev_alloc_skb(SBUFSIZE + HW_HDR_LEN)) != NULL)
		skb_reserve(bcs->skb, HW_HDR_LEN);
	else
		dev_err(bcs->cs->dev, "could not allocate skb\n");
	bcs->fcs = PPP_INITFCS;
}