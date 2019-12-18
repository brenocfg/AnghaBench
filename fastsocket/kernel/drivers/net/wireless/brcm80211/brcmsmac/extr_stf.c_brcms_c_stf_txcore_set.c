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
typedef  size_t u8 ;
struct brcms_c_info {int /*<<< orphan*/  bcn_rspec; scalar_t__ clk; TYPE_2__* stf; TYPE_3__* hw; TYPE_1__* pub; } ;
struct TYPE_6__ {int /*<<< orphan*/  d11core; } ;
struct TYPE_5__ {scalar_t__ txstreams; size_t txchain; size_t* txcore; size_t phytxant; } ;
struct TYPE_4__ {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 size_t PHY_TXC_ANT_SHIFT ; 
 int /*<<< orphan*/  brcms_b_txant_set (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  brcms_c_beacon_phytxctl_txant_upd (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_enable_mac (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_suspend_mac_and_wait (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_dbg_ht (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 scalar_t__ hweight8 (size_t) ; 

__attribute__((used)) static int brcms_c_stf_txcore_set(struct brcms_c_info *wlc, u8 Nsts,
				  u8 core_mask)
{
	brcms_dbg_ht(wlc->hw->d11core, "wl%d: Nsts %d core_mask %x\n",
		     wlc->pub->unit, Nsts, core_mask);

	if (hweight8(core_mask) > wlc->stf->txstreams)
		core_mask = 0;

	if ((hweight8(core_mask) == wlc->stf->txstreams) &&
	    ((core_mask & ~wlc->stf->txchain)
	     || !(core_mask & wlc->stf->txchain)))
		core_mask = wlc->stf->txchain;

	wlc->stf->txcore[Nsts] = core_mask;
	/* Nsts = 1..4, txcore index = 1..4 */
	if (Nsts == 1) {
		/* Needs to update beacon and ucode generated response
		 * frames when 1 stream core map changed
		 */
		wlc->stf->phytxant = core_mask << PHY_TXC_ANT_SHIFT;
		brcms_b_txant_set(wlc->hw, wlc->stf->phytxant);
		if (wlc->clk) {
			brcms_c_suspend_mac_and_wait(wlc);
			brcms_c_beacon_phytxctl_txant_upd(wlc, wlc->bcn_rspec);
			brcms_c_enable_mac(wlc);
		}
	}

	return 0;
}