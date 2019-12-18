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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int nb_ecc_prev; } ;
struct ecc_settings {int old_nbctl; int nbctl_valid; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBCFG ; 
 int NBCFG_ECC_ENABLE ; 
 int /*<<< orphan*/  NBCTL ; 
 int /*<<< orphan*/  ON ; 
 int /*<<< orphan*/  amd64_info (char*) ; 
 int /*<<< orphan*/  amd64_read_pci_cfg (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  amd64_warn (char*) ; 
 int /*<<< orphan*/  amd64_write_pci_cfg (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugf0 (char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ toggle_ecc_err_reporting (struct ecc_settings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool enable_ecc_error_reporting(struct ecc_settings *s, u8 nid,
				       struct pci_dev *F3)
{
	bool ret = true;
	u32 value, mask = 0x3;		/* UECC/CECC enable */

	if (toggle_ecc_err_reporting(s, nid, ON)) {
		amd64_warn("Error enabling ECC reporting over MCGCTL!\n");
		return false;
	}

	amd64_read_pci_cfg(F3, NBCTL, &value);

	s->old_nbctl   = value & mask;
	s->nbctl_valid = true;

	value |= mask;
	amd64_write_pci_cfg(F3, NBCTL, value);

	amd64_read_pci_cfg(F3, NBCFG, &value);

	debugf0("1: node %d, NBCFG=0x%08x[DramEccEn: %d]\n",
		nid, value, !!(value & NBCFG_ECC_ENABLE));

	if (!(value & NBCFG_ECC_ENABLE)) {
		amd64_warn("DRAM ECC disabled on this node, enabling...\n");

		s->flags.nb_ecc_prev = 0;

		/* Attempt to turn on DRAM ECC Enable */
		value |= NBCFG_ECC_ENABLE;
		amd64_write_pci_cfg(F3, NBCFG, value);

		amd64_read_pci_cfg(F3, NBCFG, &value);

		if (!(value & NBCFG_ECC_ENABLE)) {
			amd64_warn("Hardware rejected DRAM ECC enable,"
				   "check memory DIMM configuration.\n");
			ret = false;
		} else {
			amd64_info("Hardware accepted DRAM ECC Enable\n");
		}
	} else {
		s->flags.nb_ecc_prev = 1;
	}

	debugf0("2: node %d, NBCFG=0x%08x[DramEccEn: %d]\n",
		nid, value, !!(value & NBCFG_ECC_ENABLE));

	return ret;
}