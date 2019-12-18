#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  scalar_t__ u16 ;
struct wiphy {int dummy; } ;
struct ssb_sprom {int board_rev; int boardflags_lo; int boardflags_hi; int boardflags2_hi; scalar_t__ boardflags2_lo; int /*<<< orphan*/  revision; } ;
struct shared_phy_params {int unit; size_t corerev; int vid; scalar_t__ did; scalar_t__ boardtype; int boardflags; scalar_t__ boardflags2; scalar_t__ boardrev; int /*<<< orphan*/  sromrev; int /*<<< orphan*/  chippkg; int /*<<< orphan*/  chiprev; scalar_t__ chip; int /*<<< orphan*/ * physhim; int /*<<< orphan*/ * sih; } ;
struct pci_dev {int vendor; scalar_t__ device; } ;
struct brcms_hardware {int unit; int _piomode; int vendorid; scalar_t__ deviceid; size_t corerev; int boardflags; int _nbands; int /*<<< orphan*/ * sih; struct bcma_device* d11core; int /*<<< orphan*/  etheraddr; TYPE_7__* band; int /*<<< orphan*/  machwcap; int /*<<< orphan*/  phy_sh; int /*<<< orphan*/ * xmtfifo_sz; int /*<<< orphan*/  machwcap_backup; scalar_t__ boardflags2; scalar_t__ boardrev; int /*<<< orphan*/  sromrev; int /*<<< orphan*/ * physhim; TYPE_7__** bandstate; struct brcms_c_info* wlc; } ;
struct brcms_c_info {int vendorid; scalar_t__ deviceid; TYPE_5__* band; struct wiphy* wiphy; TYPE_4__* core; int /*<<< orphan*/  wl; TYPE_3__* pub; struct brcms_hardware* hw; } ;
struct TYPE_10__ {size_t rev; } ;
struct bcma_device {int /*<<< orphan*/  core_index; TYPE_2__ id; TYPE_6__* bus; } ;
struct TYPE_15__ {int bandunit; int /*<<< orphan*/  CWmax; int /*<<< orphan*/  CWmin; int /*<<< orphan*/  radiorev; int /*<<< orphan*/  radioid; scalar_t__ phyrev; int /*<<< orphan*/  phytype; int /*<<< orphan*/ * pi; int /*<<< orphan*/  core_flags; void* abgphy_encore; void* bandtype; } ;
struct TYPE_9__ {int vendor; scalar_t__ type; } ;
struct TYPE_14__ {scalar_t__ hosttype; TYPE_1__ boardinfo; struct ssb_sprom sprom; struct pci_dev* host_pci; } ;
struct TYPE_13__ {int bandunit; int /*<<< orphan*/  radiorev; int /*<<< orphan*/  radioid; scalar_t__ phyrev; int /*<<< orphan*/  phytype; int /*<<< orphan*/ * pi; void* abgphy_encore; void* bandtype; } ;
struct TYPE_12__ {int /*<<< orphan*/  coreidx; } ;
struct TYPE_11__ {size_t corerev; int boardflags; int _nbands; scalar_t__ boardflags2; scalar_t__ boardrev; int /*<<< orphan*/  sromrev; int /*<<< orphan*/ * sih; } ;

/* Variables and functions */
 int /*<<< orphan*/  APHY_CWMIN ; 
 size_t ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 scalar_t__ BCM43224_CHIP_ID ; 
 scalar_t__ BCM43224_D11N_ID ; 
 scalar_t__ BCM43224_D11N_ID_VEN1 ; 
 scalar_t__ BCM43225_CHIP_ID ; 
 int /*<<< orphan*/  BCMA_CLKMODE_FAST ; 
 scalar_t__ BCMA_HOSTTYPE_PCI ; 
 int BFL_NOPLLDOWN ; 
 int BOARDREV_PROMOTABLE ; 
 int BOARDREV_PROMOTED ; 
 scalar_t__ BRCMS_ISLCNPHY (TYPE_7__*) ; 
 scalar_t__ BRCMS_ISNPHY (TYPE_7__*) ; 
 int /*<<< orphan*/  BRCMS_PLLREQ_SHARED ; 
 int /*<<< orphan*/  BRCMS_USE_COREFLAGS ; 
 void* BRCM_BAND_2G ; 
 void* BRCM_BAND_5G ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ LCNCONF_HAS (scalar_t__) ; 
 scalar_t__ NCONF_HAS (scalar_t__) ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  PHY_CWMAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 size_t XMTFIFOTBL_STARTREV ; 
 int /*<<< orphan*/ * ai_attach (TYPE_6__*) ; 
 int /*<<< orphan*/  ai_clkctl_init (int /*<<< orphan*/ *) ; 
 scalar_t__ ai_get_boardtype (int /*<<< orphan*/ *) ; 
 scalar_t__ ai_get_chip_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ai_get_chippkg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ai_get_chiprev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ai_pci_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_attach_dmapio (struct brcms_c_info*,int,int) ; 
 int /*<<< orphan*/  brcms_b_clkctl_clk (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_corereset (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_info_init (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_b_pllreq (struct brcms_hardware*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_validate_chip_access (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_b_xtal (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_chipmatch (struct bcma_device*) ; 
 int /*<<< orphan*/  brcms_c_coredisable (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_c_get_macaddr (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_isgoodchip (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_c_setxband (struct brcms_hardware*,int) ; 
 int /*<<< orphan*/  brcms_c_validboardtype (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_dbg_info (struct bcma_device*,char*,int,int,scalar_t__) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machwcap ; 
 int /*<<< orphan*/  wiphy_err (struct wiphy*,char*,int,...) ; 
 int /*<<< orphan*/ * wlc_phy_attach (int /*<<< orphan*/ ,struct bcma_device*,void*,struct wiphy*) ; 
 int /*<<< orphan*/  wlc_phy_get_coreflags (int /*<<< orphan*/ *) ; 
 void* wlc_phy_get_encore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlc_phy_get_phyversion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlc_phy_machwcap_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_shared_attach (struct shared_phy_params*) ; 
 int /*<<< orphan*/ * wlc_phy_shim_attach (struct brcms_hardware*,int /*<<< orphan*/ ,struct brcms_c_info*) ; 
 int /*<<< orphan*/ ** xmtfifo_sz ; 

__attribute__((used)) static int brcms_b_attach(struct brcms_c_info *wlc, struct bcma_device *core,
			  uint unit, bool piomode)
{
	struct brcms_hardware *wlc_hw;
	uint err = 0;
	uint j;
	bool wme = false;
	struct shared_phy_params sha_params;
	struct wiphy *wiphy = wlc->wiphy;
	struct pci_dev *pcidev = core->bus->host_pci;
	struct ssb_sprom *sprom = &core->bus->sprom;

	if (core->bus->hosttype == BCMA_HOSTTYPE_PCI)
		brcms_dbg_info(core, "wl%d: vendor 0x%x device 0x%x\n", unit,
			       pcidev->vendor,
			       pcidev->device);
	else
		brcms_dbg_info(core, "wl%d: vendor 0x%x device 0x%x\n", unit,
			       core->bus->boardinfo.vendor,
			       core->bus->boardinfo.type);

	wme = true;

	wlc_hw = wlc->hw;
	wlc_hw->wlc = wlc;
	wlc_hw->unit = unit;
	wlc_hw->band = wlc_hw->bandstate[0];
	wlc_hw->_piomode = piomode;

	/* populate struct brcms_hardware with default values  */
	brcms_b_info_init(wlc_hw);

	/*
	 * Do the hardware portion of the attach. Also initialize software
	 * state that depends on the particular hardware we are running.
	 */
	wlc_hw->sih = ai_attach(core->bus);
	if (wlc_hw->sih == NULL) {
		wiphy_err(wiphy, "wl%d: brcms_b_attach: si_attach failed\n",
			  unit);
		err = 11;
		goto fail;
	}

	/* verify again the device is supported */
	if (!brcms_c_chipmatch(core)) {
		wiphy_err(wiphy, "wl%d: brcms_b_attach: Unsupported device\n",
			 unit);
		err = 12;
		goto fail;
	}

	if (core->bus->hosttype == BCMA_HOSTTYPE_PCI) {
		wlc_hw->vendorid = pcidev->vendor;
		wlc_hw->deviceid = pcidev->device;
	} else {
		wlc_hw->vendorid = core->bus->boardinfo.vendor;
		wlc_hw->deviceid = core->bus->boardinfo.type;
	}

	wlc_hw->d11core = core;
	wlc_hw->corerev = core->id.rev;

	/* validate chip, chiprev and corerev */
	if (!brcms_c_isgoodchip(wlc_hw)) {
		err = 13;
		goto fail;
	}

	/* initialize power control registers */
	ai_clkctl_init(wlc_hw->sih);

	/* request fastclock and force fastclock for the rest of attach
	 * bring the d11 core out of reset.
	 *   For PMU chips, the first wlc_clkctl_clk is no-op since core-clk
	 *   is still false; But it will be called again inside wlc_corereset,
	 *   after d11 is out of reset.
	 */
	brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);
	brcms_b_corereset(wlc_hw, BRCMS_USE_COREFLAGS);

	if (!brcms_b_validate_chip_access(wlc_hw)) {
		wiphy_err(wiphy, "wl%d: brcms_b_attach: validate_chip_access "
			"failed\n", unit);
		err = 14;
		goto fail;
	}

	/* get the board rev, used just below */
	j = sprom->board_rev;
	/* promote srom boardrev of 0xFF to 1 */
	if (j == BOARDREV_PROMOTABLE)
		j = BOARDREV_PROMOTED;
	wlc_hw->boardrev = (u16) j;
	if (!brcms_c_validboardtype(wlc_hw)) {
		wiphy_err(wiphy, "wl%d: brcms_b_attach: Unsupported Broadcom "
			  "board type (0x%x)" " or revision level (0x%x)\n",
			  unit, ai_get_boardtype(wlc_hw->sih),
			  wlc_hw->boardrev);
		err = 15;
		goto fail;
	}
	wlc_hw->sromrev = sprom->revision;
	wlc_hw->boardflags = sprom->boardflags_lo + (sprom->boardflags_hi << 16);
	wlc_hw->boardflags2 = sprom->boardflags2_lo + (sprom->boardflags2_hi << 16);

	if (wlc_hw->boardflags & BFL_NOPLLDOWN)
		brcms_b_pllreq(wlc_hw, true, BRCMS_PLLREQ_SHARED);

	/* check device id(srom, nvram etc.) to set bands */
	if (wlc_hw->deviceid == BCM43224_D11N_ID ||
	    wlc_hw->deviceid == BCM43224_D11N_ID_VEN1 ||
	    wlc_hw->deviceid == BCM43224_CHIP_ID)
		/* Dualband boards */
		wlc_hw->_nbands = 2;
	else
		wlc_hw->_nbands = 1;

	if ((ai_get_chip_id(wlc_hw->sih) == BCM43225_CHIP_ID))
		wlc_hw->_nbands = 1;

	/* BMAC_NOTE: remove init of pub values when brcms_c_attach()
	 * unconditionally does the init of these values
	 */
	wlc->vendorid = wlc_hw->vendorid;
	wlc->deviceid = wlc_hw->deviceid;
	wlc->pub->sih = wlc_hw->sih;
	wlc->pub->corerev = wlc_hw->corerev;
	wlc->pub->sromrev = wlc_hw->sromrev;
	wlc->pub->boardrev = wlc_hw->boardrev;
	wlc->pub->boardflags = wlc_hw->boardflags;
	wlc->pub->boardflags2 = wlc_hw->boardflags2;
	wlc->pub->_nbands = wlc_hw->_nbands;

	wlc_hw->physhim = wlc_phy_shim_attach(wlc_hw, wlc->wl, wlc);

	if (wlc_hw->physhim == NULL) {
		wiphy_err(wiphy, "wl%d: brcms_b_attach: wlc_phy_shim_attach "
			"failed\n", unit);
		err = 25;
		goto fail;
	}

	/* pass all the parameters to wlc_phy_shared_attach in one struct */
	sha_params.sih = wlc_hw->sih;
	sha_params.physhim = wlc_hw->physhim;
	sha_params.unit = unit;
	sha_params.corerev = wlc_hw->corerev;
	sha_params.vid = wlc_hw->vendorid;
	sha_params.did = wlc_hw->deviceid;
	sha_params.chip = ai_get_chip_id(wlc_hw->sih);
	sha_params.chiprev = ai_get_chiprev(wlc_hw->sih);
	sha_params.chippkg = ai_get_chippkg(wlc_hw->sih);
	sha_params.sromrev = wlc_hw->sromrev;
	sha_params.boardtype = ai_get_boardtype(wlc_hw->sih);
	sha_params.boardrev = wlc_hw->boardrev;
	sha_params.boardflags = wlc_hw->boardflags;
	sha_params.boardflags2 = wlc_hw->boardflags2;

	/* alloc and save pointer to shared phy state area */
	wlc_hw->phy_sh = wlc_phy_shared_attach(&sha_params);
	if (!wlc_hw->phy_sh) {
		err = 16;
		goto fail;
	}

	/* initialize software state for each core and band */
	for (j = 0; j < wlc_hw->_nbands; j++) {
		/*
		 * band0 is always 2.4Ghz
		 * band1, if present, is 5Ghz
		 */

		brcms_c_setxband(wlc_hw, j);

		wlc_hw->band->bandunit = j;
		wlc_hw->band->bandtype = j ? BRCM_BAND_5G : BRCM_BAND_2G;
		wlc->band->bandunit = j;
		wlc->band->bandtype = j ? BRCM_BAND_5G : BRCM_BAND_2G;
		wlc->core->coreidx = core->core_index;

		wlc_hw->machwcap = bcma_read32(core, D11REGOFFS(machwcap));
		wlc_hw->machwcap_backup = wlc_hw->machwcap;

		/* init tx fifo size */
		WARN_ON((wlc_hw->corerev - XMTFIFOTBL_STARTREV) < 0 ||
			(wlc_hw->corerev - XMTFIFOTBL_STARTREV) >
				ARRAY_SIZE(xmtfifo_sz));
		wlc_hw->xmtfifo_sz =
		    xmtfifo_sz[(wlc_hw->corerev - XMTFIFOTBL_STARTREV)];
		WARN_ON(!wlc_hw->xmtfifo_sz[0]);

		/* Get a phy for this band */
		wlc_hw->band->pi =
			wlc_phy_attach(wlc_hw->phy_sh, core,
				       wlc_hw->band->bandtype,
				       wlc->wiphy);
		if (wlc_hw->band->pi == NULL) {
			wiphy_err(wiphy, "wl%d: brcms_b_attach: wlc_phy_"
				  "attach failed\n", unit);
			err = 17;
			goto fail;
		}

		wlc_phy_machwcap_set(wlc_hw->band->pi, wlc_hw->machwcap);

		wlc_phy_get_phyversion(wlc_hw->band->pi, &wlc_hw->band->phytype,
				       &wlc_hw->band->phyrev,
				       &wlc_hw->band->radioid,
				       &wlc_hw->band->radiorev);
		wlc_hw->band->abgphy_encore =
		    wlc_phy_get_encore(wlc_hw->band->pi);
		wlc->band->abgphy_encore = wlc_phy_get_encore(wlc_hw->band->pi);
		wlc_hw->band->core_flags =
		    wlc_phy_get_coreflags(wlc_hw->band->pi);

		/* verify good phy_type & supported phy revision */
		if (BRCMS_ISNPHY(wlc_hw->band)) {
			if (NCONF_HAS(wlc_hw->band->phyrev))
				goto good_phy;
			else
				goto bad_phy;
		} else if (BRCMS_ISLCNPHY(wlc_hw->band)) {
			if (LCNCONF_HAS(wlc_hw->band->phyrev))
				goto good_phy;
			else
				goto bad_phy;
		} else {
 bad_phy:
			wiphy_err(wiphy, "wl%d: brcms_b_attach: unsupported "
				  "phy type/rev (%d/%d)\n", unit,
				  wlc_hw->band->phytype, wlc_hw->band->phyrev);
			err = 18;
			goto fail;
		}

 good_phy:
		/*
		 * BMAC_NOTE: wlc->band->pi should not be set below and should
		 * be done in the high level attach. However we can not make
		 * that change until all low level access is changed to
		 * wlc_hw->band->pi. Instead do the wlc->band->pi init below,
		 * keeping wlc_hw->band->pi as well for incremental update of
		 * low level fns, and cut over low only init when all fns
		 * updated.
		 */
		wlc->band->pi = wlc_hw->band->pi;
		wlc->band->phytype = wlc_hw->band->phytype;
		wlc->band->phyrev = wlc_hw->band->phyrev;
		wlc->band->radioid = wlc_hw->band->radioid;
		wlc->band->radiorev = wlc_hw->band->radiorev;

		/* default contention windows size limits */
		wlc_hw->band->CWmin = APHY_CWMIN;
		wlc_hw->band->CWmax = PHY_CWMAX;

		if (!brcms_b_attach_dmapio(wlc, j, wme)) {
			err = 19;
			goto fail;
		}
	}

	/* disable core to match driver "down" state */
	brcms_c_coredisable(wlc_hw);

	/* Match driver "down" state */
	ai_pci_down(wlc_hw->sih);

	/* turn off pll and xtal to match driver "down" state */
	brcms_b_xtal(wlc_hw, OFF);

	/* *******************************************************************
	 * The hardware is in the DOWN state at this point. D11 core
	 * or cores are in reset with clocks off, and the board PLLs
	 * are off if possible.
	 *
	 * Beyond this point, wlc->sbclk == false and chip registers
	 * should not be touched.
	 *********************************************************************
	 */

	/* init etheraddr state variables */
	brcms_c_get_macaddr(wlc_hw, wlc_hw->etheraddr);

	if (is_broadcast_ether_addr(wlc_hw->etheraddr) ||
	    is_zero_ether_addr(wlc_hw->etheraddr)) {
		wiphy_err(wiphy, "wl%d: brcms_b_attach: bad macaddr\n",
			  unit);
		err = 22;
		goto fail;
	}

	brcms_dbg_info(wlc_hw->d11core, "deviceid 0x%x nbands %d board 0x%x\n",
		       wlc_hw->deviceid, wlc_hw->_nbands,
		       ai_get_boardtype(wlc_hw->sih));

	return err;

 fail:
	wiphy_err(wiphy, "wl%d: brcms_b_attach: failed with err %d\n", unit,
		  err);
	return err;
}