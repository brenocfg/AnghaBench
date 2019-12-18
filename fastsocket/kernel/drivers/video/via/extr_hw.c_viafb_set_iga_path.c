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
struct TYPE_12__ {TYPE_5__* tmds_setting_info; TYPE_4__* lvds_setting_info; TYPE_3__* crt_setting_info; TYPE_2__* lvds_setting_info2; TYPE_1__* chip_info; } ;
struct TYPE_11__ {void* iga_path; } ;
struct TYPE_10__ {void* iga_path; } ;
struct TYPE_9__ {void* iga_path; } ;
struct TYPE_8__ {void* iga_path; } ;
struct TYPE_7__ {scalar_t__ gfx_chip_name; } ;

/* Variables and functions */
 scalar_t__ CRT_Device ; 
 scalar_t__ DVI_Device ; 
 void* IGA1 ; 
 void* IGA2 ; 
 scalar_t__ LCD2_Device ; 
 scalar_t__ LCD_Device ; 
 scalar_t__ UNICHROME_CLE266 ; 
 scalar_t__ viafb_CRT_ON ; 
 scalar_t__ viafb_DVI_ON ; 
 scalar_t__ viafb_LCD2_ON ; 
 scalar_t__ viafb_LCD_ON ; 
 int viafb_SAMM_ON ; 
 scalar_t__ viafb_dual_fb ; 
 scalar_t__ viafb_primary_dev ; 
 TYPE_6__* viaparinfo ; 

void viafb_set_iga_path(void)
{

	if (viafb_SAMM_ON == 1) {
		if (viafb_CRT_ON) {
			if (viafb_primary_dev == CRT_Device)
				viaparinfo->crt_setting_info->iga_path = IGA1;
			else
				viaparinfo->crt_setting_info->iga_path = IGA2;
		}

		if (viafb_DVI_ON) {
			if (viafb_primary_dev == DVI_Device)
				viaparinfo->tmds_setting_info->iga_path = IGA1;
			else
				viaparinfo->tmds_setting_info->iga_path = IGA2;
		}

		if (viafb_LCD_ON) {
			if (viafb_primary_dev == LCD_Device) {
				if (viafb_dual_fb &&
					(viaparinfo->chip_info->gfx_chip_name ==
					UNICHROME_CLE266)) {
					viaparinfo->
					lvds_setting_info->iga_path = IGA2;
					viaparinfo->
					crt_setting_info->iga_path = IGA1;
					viaparinfo->
					tmds_setting_info->iga_path = IGA1;
				} else
					viaparinfo->
					lvds_setting_info->iga_path = IGA1;
			} else {
				viaparinfo->lvds_setting_info->iga_path = IGA2;
			}
		}
		if (viafb_LCD2_ON) {
			if (LCD2_Device == viafb_primary_dev)
				viaparinfo->lvds_setting_info2->iga_path = IGA1;
			else
				viaparinfo->lvds_setting_info2->iga_path = IGA2;
		}
	} else {
		viafb_SAMM_ON = 0;

		if (viafb_CRT_ON && viafb_LCD_ON) {
			viaparinfo->crt_setting_info->iga_path = IGA1;
			viaparinfo->lvds_setting_info->iga_path = IGA2;
		} else if (viafb_CRT_ON && viafb_DVI_ON) {
			viaparinfo->crt_setting_info->iga_path = IGA1;
			viaparinfo->tmds_setting_info->iga_path = IGA2;
		} else if (viafb_LCD_ON && viafb_DVI_ON) {
			viaparinfo->tmds_setting_info->iga_path = IGA1;
			viaparinfo->lvds_setting_info->iga_path = IGA2;
		} else if (viafb_LCD_ON && viafb_LCD2_ON) {
			viaparinfo->lvds_setting_info->iga_path = IGA2;
			viaparinfo->lvds_setting_info2->iga_path = IGA2;
		} else if (viafb_CRT_ON) {
			viaparinfo->crt_setting_info->iga_path = IGA1;
		} else if (viafb_LCD_ON) {
			viaparinfo->lvds_setting_info->iga_path = IGA2;
		} else if (viafb_DVI_ON) {
			viaparinfo->tmds_setting_info->iga_path = IGA1;
		}
	}
}