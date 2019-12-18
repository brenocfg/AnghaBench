#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int extpa_gain; } ;
struct TYPE_10__ {int extpa_gain; } ;
struct TYPE_12__ {TYPE_5__ ghz5; TYPE_4__ ghz2; } ;
struct ssb_sprom {int revision; int boardflags2_lo; TYPE_6__ fem; } ;
struct pci_dev {int device; } ;
struct b43_phy {int rev; struct b43_phy_n* n; } ;
struct b43_wldev {struct b43_phy phy; TYPE_3__* dev; } ;
struct b43_phy_n {int hang_avoid; int init_por; int gain_boost; int txrx_chain; int phyrxchain; int perical; int* tx_pwr_idx; int txpwrctrl; int pwg_gain_5ghz; int ipa2g_on; int ipa5g_on; int /*<<< orphan*/  spur_avoid; } ;
struct TYPE_9__ {scalar_t__ board_vendor; int core_rev; scalar_t__ bus_type; TYPE_2__* sdev; struct ssb_sprom* bus_sprom; } ;
struct TYPE_8__ {TYPE_1__* bus; } ;
struct TYPE_7__ {scalar_t__ bustype; struct pci_dev* host_pci; } ;

/* Variables and functions */
 int B43_BFL2_5G_PWRGAIN ; 
 int B43_BFL2_TXPWRCTRL_EN ; 
 scalar_t__ B43_BUS_SSB ; 
 int /*<<< orphan*/  B43_SPUR_AVOID_AUTO ; 
 int /*<<< orphan*/  B43_SPUR_AVOID_DISABLE ; 
 scalar_t__ PCI_VENDOR_ID_APPLE ; 
 scalar_t__ SSB_BUSTYPE_PCI ; 
 int /*<<< orphan*/  memset (struct b43_phy_n*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_nphy_op_prepare_structs(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_n *nphy = phy->n;
	struct ssb_sprom *sprom = dev->dev->bus_sprom;

	memset(nphy, 0, sizeof(*nphy));

	nphy->hang_avoid = (phy->rev == 3 || phy->rev == 4);
	nphy->spur_avoid = (phy->rev >= 3) ?
				B43_SPUR_AVOID_AUTO : B43_SPUR_AVOID_DISABLE;
	nphy->init_por = true;
	nphy->gain_boost = true; /* this way we follow wl, assume it is true */
	nphy->txrx_chain = 2; /* sth different than 0 and 1 for now */
	nphy->phyrxchain = 3; /* to avoid b43_nphy_set_rx_core_state like wl */
	nphy->perical = 2; /* avoid additional rssi cal on init (like wl) */
	/* 128 can mean disabled-by-default state of TX pwr ctl. Max value is
	 * 0x7f == 127 and we check for 128 when restoring TX pwr ctl. */
	nphy->tx_pwr_idx[0] = 128;
	nphy->tx_pwr_idx[1] = 128;

	/* Hardware TX power control and 5GHz power gain */
	nphy->txpwrctrl = false;
	nphy->pwg_gain_5ghz = false;
	if (dev->phy.rev >= 3 ||
	    (dev->dev->board_vendor == PCI_VENDOR_ID_APPLE &&
	     (dev->dev->core_rev == 11 || dev->dev->core_rev == 12))) {
		nphy->txpwrctrl = true;
		nphy->pwg_gain_5ghz = true;
	} else if (sprom->revision >= 4) {
		if (dev->phy.rev >= 2 &&
		    (sprom->boardflags2_lo & B43_BFL2_TXPWRCTRL_EN)) {
			nphy->txpwrctrl = true;
#ifdef CONFIG_B43_SSB
			if (dev->dev->bus_type == B43_BUS_SSB &&
			    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI) {
				struct pci_dev *pdev =
					dev->dev->sdev->bus->host_pci;
				if (pdev->device == 0x4328 ||
				    pdev->device == 0x432a)
					nphy->pwg_gain_5ghz = true;
			}
#endif
		} else if (sprom->boardflags2_lo & B43_BFL2_5G_PWRGAIN) {
			nphy->pwg_gain_5ghz = true;
		}
	}

	if (dev->phy.rev >= 3) {
		nphy->ipa2g_on = sprom->fem.ghz2.extpa_gain == 2;
		nphy->ipa5g_on = sprom->fem.ghz5.extpa_gain == 2;
	}

	nphy->init_por = true;
}