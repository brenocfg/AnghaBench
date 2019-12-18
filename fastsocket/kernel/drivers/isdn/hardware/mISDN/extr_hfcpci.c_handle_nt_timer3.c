#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mst_m; scalar_t__ nt_timer; int /*<<< orphan*/  int_m1; } ;
struct hfc_pci {TYPE_1__ hw; int /*<<< orphan*/  cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  D; } ;
struct dchannel {TYPE_2__ dev; int /*<<< orphan*/  Flags; struct hfc_pci* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_ACTIVE ; 
 int /*<<< orphan*/  FLG_HFC_TIMER_T3 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HFCPCI_INTS_TIMER ; 
 int /*<<< orphan*/  HFCPCI_INT_M1 ; 
 int /*<<< orphan*/  HFCPCI_MASTER ; 
 int /*<<< orphan*/  HFCPCI_MST_MODE ; 
 int /*<<< orphan*/  HFC_CFG_MASTER ; 
 int /*<<< orphan*/  MISDN_ID_ANY ; 
 int /*<<< orphan*/  PH_ACTIVATE_IND ; 
 int /*<<< orphan*/  Write_hfc (struct hfc_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _queue_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
handle_nt_timer3(struct dchannel *dch) {
	struct hfc_pci	*hc = dch->hw;

	test_and_clear_bit(FLG_HFC_TIMER_T3, &dch->Flags);
	hc->hw.int_m1 &= ~HFCPCI_INTS_TIMER;
	Write_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
	hc->hw.nt_timer = 0;
	test_and_set_bit(FLG_ACTIVE, &dch->Flags);
	if (test_bit(HFC_CFG_MASTER, &hc->cfg))
		hc->hw.mst_m |= HFCPCI_MASTER;
	Write_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
	_queue_data(&dch->dev.D, PH_ACTIVATE_IND,
	    MISDN_ID_ANY, 0, NULL, GFP_ATOMIC);
}