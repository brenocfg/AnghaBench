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
typedef  scalar_t__ u8 ;
struct TYPE_8__ {scalar_t__ mode_type; int max_concurr_spin_up; int do_enable_ssc; scalar_t__ ssc_sata_tx_spread_level; scalar_t__ ssc_sas_tx_spread_level; int ssc_sas_tx_type; } ;
struct sci_oem_params {TYPE_4__ controller; TYPE_3__* ports; TYPE_2__* phys; } ;
struct TYPE_7__ {scalar_t__ phy_mask; } ;
struct TYPE_5__ {scalar_t__ high; scalar_t__ low; } ;
struct TYPE_6__ {TYPE_1__ sas_address; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ISCI_ROM_VER_1_1 ; 
 int MAX_CONCURRENT_DEVICE_SPIN_UP_COUNT ; 
 scalar_t__ SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE ; 
 scalar_t__ SCIC_PORT_MANUAL_CONFIGURATION_MODE ; 
 scalar_t__ SCIC_SDS_PARM_PHY_MASK_MAX ; 
 int SCI_MAX_PHYS ; 
 int SCI_MAX_PORTS ; 

int sci_oem_parameters_validate(struct sci_oem_params *oem, u8 version)
{
	int i;

	for (i = 0; i < SCI_MAX_PORTS; i++)
		if (oem->ports[i].phy_mask > SCIC_SDS_PARM_PHY_MASK_MAX)
			return -EINVAL;

	for (i = 0; i < SCI_MAX_PHYS; i++)
		if (oem->phys[i].sas_address.high == 0 &&
		    oem->phys[i].sas_address.low == 0)
			return -EINVAL;

	if (oem->controller.mode_type == SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE) {
		for (i = 0; i < SCI_MAX_PHYS; i++)
			if (oem->ports[i].phy_mask != 0)
				return -EINVAL;
	} else if (oem->controller.mode_type == SCIC_PORT_MANUAL_CONFIGURATION_MODE) {
		u8 phy_mask = 0;

		for (i = 0; i < SCI_MAX_PHYS; i++)
			phy_mask |= oem->ports[i].phy_mask;

		if (phy_mask == 0)
			return -EINVAL;
	} else
		return -EINVAL;

	if (oem->controller.max_concurr_spin_up > MAX_CONCURRENT_DEVICE_SPIN_UP_COUNT ||
	    oem->controller.max_concurr_spin_up < 1)
		return -EINVAL;

	if (oem->controller.do_enable_ssc) {
		if (version < ISCI_ROM_VER_1_1 && oem->controller.do_enable_ssc != 1)
			return -EINVAL;

		if (version >= ISCI_ROM_VER_1_1) {
			u8 test = oem->controller.ssc_sata_tx_spread_level;

			switch (test) {
			case 0:
			case 2:
			case 3:
			case 6:
			case 7:
				break;
			default:
				return -EINVAL;
			}

			test = oem->controller.ssc_sas_tx_spread_level;
			if (oem->controller.ssc_sas_tx_type == 0) {
				switch (test) {
				case 0:
				case 2:
				case 3:
					break;
				default:
					return -EINVAL;
				}
			} else if (oem->controller.ssc_sas_tx_type == 1) {
				switch (test) {
				case 0:
				case 3:
				case 6:
					break;
				default:
					return -EINVAL;
				}
			}
		}
	}

	return 0;
}