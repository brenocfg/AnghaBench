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
typedef  int /*<<< orphan*/  u_long ;
struct hfc_pci {int /*<<< orphan*/  lock; } ;
struct bchannel {int /*<<< orphan*/  nr; struct hfc_pci* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_P_NONE ; 
 int /*<<< orphan*/  mISDN_clear_bchannel (struct bchannel*) ; 
 int /*<<< orphan*/  mode_hfcpci (struct bchannel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
deactivate_bchannel(struct bchannel *bch)
{
	struct hfc_pci	*hc = bch->hw;
	u_long		flags;

	spin_lock_irqsave(&hc->lock, flags);
	mISDN_clear_bchannel(bch);
	mode_hfcpci(bch, bch->nr, ISDN_P_NONE);
	spin_unlock_irqrestore(&hc->lock, flags);
}