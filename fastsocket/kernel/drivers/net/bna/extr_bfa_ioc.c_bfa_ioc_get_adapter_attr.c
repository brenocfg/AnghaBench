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
struct bfi_ioc_attr {int /*<<< orphan*/  asic_rev; int /*<<< orphan*/  pcie_lanes_orig; int /*<<< orphan*/  pcie_lanes; int /*<<< orphan*/  pcie_gen; int /*<<< orphan*/  adapter_prop; int /*<<< orphan*/  card_type; int /*<<< orphan*/  vpd; } ;
struct bfa_mfg_vpd {int dummy; } ;
struct bfa_ioc {struct bfi_ioc_attr* attr; } ;
struct bfa_adapter_attr {int prototype; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  asic_rev; int /*<<< orphan*/  pcie_lanes_orig; int /*<<< orphan*/  pcie_lanes; int /*<<< orphan*/  pcie_gen; int /*<<< orphan*/  mac; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  is_mezz; int /*<<< orphan*/  card_type; int /*<<< orphan*/  model_descr; int /*<<< orphan*/  model; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  nports; int /*<<< orphan*/  vpd; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  optrom_ver; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  serial_num; } ;

/* Variables and functions */
 scalar_t__ BFI_ADAPTER_IS_SPECIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_get_adapter_fw_ver (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_get_adapter_manufacturer (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_get_adapter_model (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_get_adapter_optrom_ver (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_get_adapter_serial_num (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_get_nports (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_get_pci_chip_rev (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_get_pwwn (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_speed_sup (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_mfg_is_mezz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_get_mac (struct bfa_ioc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
bfa_ioc_get_adapter_attr(struct bfa_ioc *ioc,
			 struct bfa_adapter_attr *ad_attr)
{
	struct bfi_ioc_attr *ioc_attr;

	ioc_attr = ioc->attr;

	bfa_ioc_get_adapter_serial_num(ioc, ad_attr->serial_num);
	bfa_ioc_get_adapter_fw_ver(ioc, ad_attr->fw_ver);
	bfa_ioc_get_adapter_optrom_ver(ioc, ad_attr->optrom_ver);
	bfa_ioc_get_adapter_manufacturer(ioc, ad_attr->manufacturer);
	memcpy(&ad_attr->vpd, &ioc_attr->vpd,
		      sizeof(struct bfa_mfg_vpd));

	ad_attr->nports = bfa_ioc_get_nports(ioc);
	ad_attr->max_speed = bfa_ioc_speed_sup(ioc);

	bfa_ioc_get_adapter_model(ioc, ad_attr->model);
	/* For now, model descr uses same model string */
	bfa_ioc_get_adapter_model(ioc, ad_attr->model_descr);

	ad_attr->card_type = ioc_attr->card_type;
	ad_attr->is_mezz = bfa_mfg_is_mezz(ioc_attr->card_type);

	if (BFI_ADAPTER_IS_SPECIAL(ioc_attr->adapter_prop))
		ad_attr->prototype = 1;
	else
		ad_attr->prototype = 0;

	ad_attr->pwwn = bfa_ioc_get_pwwn(ioc);
	ad_attr->mac  = bfa_nw_ioc_get_mac(ioc);

	ad_attr->pcie_gen = ioc_attr->pcie_gen;
	ad_attr->pcie_lanes = ioc_attr->pcie_lanes;
	ad_attr->pcie_lanes_orig = ioc_attr->pcie_lanes_orig;
	ad_attr->asic_rev = ioc_attr->asic_rev;

	bfa_ioc_get_pci_chip_rev(ioc, ad_attr->hw_ver);
}