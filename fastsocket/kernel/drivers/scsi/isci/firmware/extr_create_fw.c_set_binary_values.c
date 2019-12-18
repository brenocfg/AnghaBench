#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int high; int low; } ;
struct sci_phy_oem_params {int /*<<< orphan*/  afe_tx_amp_control3; int /*<<< orphan*/  afe_tx_amp_control2; int /*<<< orphan*/  afe_tx_amp_control1; int /*<<< orphan*/  afe_tx_amp_control0; TYPE_3__ sas_address; } ;
struct TYPE_8__ {int cable_selection_mask; int /*<<< orphan*/  do_enable_ssc; int /*<<< orphan*/  max_concurr_spin_up; int /*<<< orphan*/  mode_type; } ;
struct sci_oem_params {TYPE_4__ controller; struct sci_phy_oem_params* phys; TYPE_2__* ports; } ;
struct sci_bios_oem_param_block_hdr {int dummy; } ;
struct TYPE_5__ {int total_block_length; int hdr_length; int /*<<< orphan*/  num_elements; int /*<<< orphan*/  version; int /*<<< orphan*/  signature; } ;
struct isci_orom {struct sci_oem_params* ctrl; TYPE_1__ hdr; } ;
typedef  int __u8 ;
struct TYPE_6__ {int /*<<< orphan*/  phy_mask; } ;

/* Variables and functions */
 int SCI_MAX_PHYS ; 
 int SCI_MAX_PORTS ; 
 int /*<<< orphan*/  afe_tx_amp_control0 ; 
 int /*<<< orphan*/  afe_tx_amp_control1 ; 
 int /*<<< orphan*/  afe_tx_amp_control2 ; 
 int /*<<< orphan*/  afe_tx_amp_control3 ; 
 int** cable_selection ; 
 int /*<<< orphan*/  enable_ssc ; 
 int /*<<< orphan*/  max_num_concurrent_dev_spin_up ; 
 int /*<<< orphan*/  mode_type ; 
 int /*<<< orphan*/  num_elements ; 
 int /*<<< orphan*/ ** phy_mask ; 
 int** sas_addr ; 
 int /*<<< orphan*/  sig ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  version ; 

void set_binary_values(struct isci_orom *isci_orom)
{
	int c, phy_idx, port_idx;

	/* setting OROM signature */
	strncpy(isci_orom->hdr.signature, sig, strlen(sig));
	isci_orom->hdr.version = version;
	isci_orom->hdr.total_block_length = sizeof(struct isci_orom);
	isci_orom->hdr.hdr_length = sizeof(struct sci_bios_oem_param_block_hdr);
	isci_orom->hdr.num_elements = num_elements;

	for (c = 0; c < 2; c++) {
		struct sci_oem_params *ctrl = &isci_orom->ctrl[c];
		__u8 cable_selection_mask = 0;

		ctrl->controller.mode_type = mode_type;
		ctrl->controller.max_concurr_spin_up = max_num_concurrent_dev_spin_up;
		ctrl->controller.do_enable_ssc = enable_ssc;

		for (port_idx = 0; port_idx < SCI_MAX_PORTS; port_idx++)
			ctrl->ports[port_idx].phy_mask = phy_mask[c][port_idx];

		for (phy_idx = 0; phy_idx < SCI_MAX_PHYS; phy_idx++) {
			struct sci_phy_oem_params *phy = &ctrl->phys[phy_idx];
			__u8 cable_phy = cable_selection[c][phy_idx];

			phy->sas_address.high = sas_addr[c][phy_idx] >> 32;
			phy->sas_address.low = sas_addr[c][phy_idx];

			phy->afe_tx_amp_control0 = afe_tx_amp_control0;
			phy->afe_tx_amp_control1 = afe_tx_amp_control1;
			phy->afe_tx_amp_control2 = afe_tx_amp_control2;
			phy->afe_tx_amp_control3 = afe_tx_amp_control3;

			cable_selection_mask |= (cable_phy & 1) << phy_idx;
			cable_selection_mask |= (cable_phy & 2) << (phy_idx + 3);
		}
		ctrl->controller.cable_selection_mask = cable_selection_mask;
	}
}