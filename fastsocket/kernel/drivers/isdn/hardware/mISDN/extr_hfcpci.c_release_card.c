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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_6__ {int /*<<< orphan*/ * function; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  l1; TYPE_3__ timer; } ;
struct TYPE_4__ {scalar_t__ protocol; scalar_t__ int_m2; } ;
struct hfc_pci {int /*<<< orphan*/  pdev; TYPE_2__ dch; int /*<<< orphan*/ * bch; int /*<<< orphan*/  irq; scalar_t__ initdone; TYPE_1__ hw; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_CHANNEL ; 
 int /*<<< orphan*/  ISDN_P_NONE ; 
 scalar_t__ ISDN_P_TE_S0 ; 
 int /*<<< orphan*/  del_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  disable_hwirq (struct hfc_pci*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hfc_pci*) ; 
 int /*<<< orphan*/  kfree (struct hfc_pci*) ; 
 int /*<<< orphan*/  l1_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_freebchannel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_freedchannel (TYPE_2__*) ; 
 int /*<<< orphan*/  mISDN_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_hfcpci (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_io_hfcpci (struct hfc_pci*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
release_card(struct hfc_pci *hc) {
	u_long	flags;

	spin_lock_irqsave(&hc->lock, flags);
	hc->hw.int_m2 = 0; /* interrupt output off ! */
	disable_hwirq(hc);
	mode_hfcpci(&hc->bch[0], 1, ISDN_P_NONE);
	mode_hfcpci(&hc->bch[1], 2, ISDN_P_NONE);
	if (hc->dch.timer.function != NULL) {
		del_timer(&hc->dch.timer);
		hc->dch.timer.function = NULL;
	}
	spin_unlock_irqrestore(&hc->lock, flags);
	if (hc->hw.protocol == ISDN_P_TE_S0)
		l1_event(hc->dch.l1, CLOSE_CHANNEL);
	if (hc->initdone)
		free_irq(hc->irq, hc);
	release_io_hfcpci(hc); /* must release after free_irq! */
	mISDN_unregister_device(&hc->dch.dev);
	mISDN_freebchannel(&hc->bch[1]);
	mISDN_freebchannel(&hc->bch[0]);
	mISDN_freedchannel(&hc->dch);
	pci_set_drvdata(hc->pdev, NULL);
	kfree(hc);
}