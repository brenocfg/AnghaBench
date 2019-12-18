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
struct lvds_setting_information {int dummy; } ;
struct lvds_chip_information {scalar_t__ output_interface; int lvds_chip_name; } ;
struct TYPE_4__ {TYPE_1__* chip_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  gfx_chip_name; } ;

/* Variables and functions */
#define  INTEGRATED_LVDS 134 
 scalar_t__ INTERFACE_DFP ; 
 void* INTERFACE_DFP_LOW ; 
 scalar_t__ INTERFACE_DVP0 ; 
 scalar_t__ INTERFACE_DVP1 ; 
 scalar_t__ INTERFACE_NONE ; 
#define  UNICHROME_CN700 133 
#define  UNICHROME_CX700 132 
#define  UNICHROME_K8M890 131 
#define  UNICHROME_P4M890 130 
#define  UNICHROME_P4M900 129 
#define  VT1636_LVDS 128 
 int /*<<< orphan*/  check_diport_of_integrated_lvds (struct lvds_chip_information*,struct lvds_setting_information*) ; 
 TYPE_2__* viaparinfo ; 

void viafb_init_lvds_output_interface(struct lvds_chip_information
				*plvds_chip_info,
				struct lvds_setting_information
				*plvds_setting_info)
{
	if (INTERFACE_NONE != plvds_chip_info->output_interface) {
		/*Do nothing, lcd port is specified by module parameter */
		return;
	}

	switch (plvds_chip_info->lvds_chip_name) {

	case VT1636_LVDS:
		switch (viaparinfo->chip_info->gfx_chip_name) {
		case UNICHROME_CX700:
			plvds_chip_info->output_interface = INTERFACE_DVP1;
			break;
		case UNICHROME_CN700:
			plvds_chip_info->output_interface = INTERFACE_DFP_LOW;
			break;
		default:
			plvds_chip_info->output_interface = INTERFACE_DVP0;
			break;
		}
		break;

	case INTEGRATED_LVDS:
		check_diport_of_integrated_lvds(plvds_chip_info,
						plvds_setting_info);
		break;

	default:
		switch (viaparinfo->chip_info->gfx_chip_name) {
		case UNICHROME_K8M890:
		case UNICHROME_P4M900:
		case UNICHROME_P4M890:
			plvds_chip_info->output_interface = INTERFACE_DFP_LOW;
			break;
		default:
			plvds_chip_info->output_interface = INTERFACE_DFP;
			break;
		}
		break;
	}
}