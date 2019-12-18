#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct brcms_hardware {int /*<<< orphan*/  sih; TYPE_2__* d11core; int /*<<< orphan*/  unit; } ;
struct TYPE_5__ {TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/ * drv_pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CLKMODE_FAST ; 
 int /*<<< orphan*/  BRCMS_USE_COREFLAGS ; 
 int ENOMEDIUM ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 int /*<<< orphan*/  ai_clkctl_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ai_pci_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ai_pci_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_core_pci_irq_ctl (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  brcms_b_clkctl_clk (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_corereset (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 scalar_t__ brcms_b_radio_read_hwdisabled (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_b_xtal (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_dbg_info (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcms_b_up_prep(struct brcms_hardware *wlc_hw)
{
	brcms_dbg_info(wlc_hw->d11core, "wl%d\n", wlc_hw->unit);

	/*
	 * Enable pll and xtal, initialize the power control registers,
	 * and force fastclock for the remainder of brcms_c_up().
	 */
	brcms_b_xtal(wlc_hw, ON);
	ai_clkctl_init(wlc_hw->sih);
	brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);

	/*
	 * Configure pci/pcmcia here instead of in brcms_c_attach()
	 * to allow mfg hotswap:  down, hotswap (chip power cycle), up.
	 */
	bcma_core_pci_irq_ctl(&wlc_hw->d11core->bus->drv_pci[0], wlc_hw->d11core,
			      true);

	/*
	 * Need to read the hwradio status here to cover the case where the
	 * system is loaded with the hw radio disabled. We do not want to
	 * bring the driver up in this case.
	 */
	if (brcms_b_radio_read_hwdisabled(wlc_hw)) {
		/* put SB PCI in down state again */
		ai_pci_down(wlc_hw->sih);
		brcms_b_xtal(wlc_hw, OFF);
		return -ENOMEDIUM;
	}

	ai_pci_up(wlc_hw->sih);

	/* reset the d11 core */
	brcms_b_corereset(wlc_hw, BRCMS_USE_COREFLAGS);

	return 0;
}