#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bc_state {int /*<<< orphan*/  fcs; TYPE_1__* cs; int /*<<< orphan*/ * skb; int /*<<< orphan*/  ignore; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HW_HDR_LEN ; 
 int /*<<< orphan*/  PPP_INITFCS ; 
 scalar_t__ SBUFSIZE ; 
 int /*<<< orphan*/ * dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_trim (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hdlc_flush(struct bc_state *bcs)
{
	/* clear skb or allocate new if not skipping */
	if (likely(bcs->skb != NULL))
		skb_trim(bcs->skb, 0);
	else if (!bcs->ignore) {
		if ((bcs->skb = dev_alloc_skb(SBUFSIZE + HW_HDR_LEN)) != NULL)
			skb_reserve(bcs->skb, HW_HDR_LEN);
		else
			dev_err(bcs->cs->dev, "could not allocate skb\n");
	}

	/* reset packet state */
	bcs->fcs = PPP_INITFCS;
}