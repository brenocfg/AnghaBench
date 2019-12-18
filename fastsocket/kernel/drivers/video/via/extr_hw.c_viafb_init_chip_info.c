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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_8__ {TYPE_2__* lvds_setting_info; TYPE_1__* lvds_setting_info2; TYPE_3__* crt_setting_info; } ;
struct TYPE_7__ {int /*<<< orphan*/  refresh_rate; int /*<<< orphan*/  iga_path; } ;
struct TYPE_6__ {int /*<<< orphan*/  lcd_mode; int /*<<< orphan*/  display_method; int /*<<< orphan*/  get_lcd_size_method; } ;
struct TYPE_5__ {int /*<<< orphan*/  lcd_mode; int /*<<< orphan*/  display_method; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LCD_SIZE_BY_USER_SETTING ; 
 int /*<<< orphan*/  IGA1 ; 
 int /*<<< orphan*/  init_gfx_chip_info (struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  init_lvds_chip_info () ; 
 int /*<<< orphan*/  init_tmds_chip_info () ; 
 int /*<<< orphan*/  viafb_lcd_dsp_method ; 
 int /*<<< orphan*/  viafb_lcd_mode ; 
 int /*<<< orphan*/  viafb_refresh ; 
 int /*<<< orphan*/  viafb_set_iga_path () ; 
 TYPE_4__* viaparinfo ; 

void viafb_init_chip_info(struct pci_dev *pdev,
			  const struct pci_device_id *pdi)
{
	init_gfx_chip_info(pdev, pdi);
	init_tmds_chip_info();
	init_lvds_chip_info();

	viaparinfo->crt_setting_info->iga_path = IGA1;
	viaparinfo->crt_setting_info->refresh_rate = viafb_refresh;

	/*Set IGA path for each device */
	viafb_set_iga_path();

	viaparinfo->lvds_setting_info->display_method = viafb_lcd_dsp_method;
	viaparinfo->lvds_setting_info->get_lcd_size_method =
		GET_LCD_SIZE_BY_USER_SETTING;
	viaparinfo->lvds_setting_info->lcd_mode = viafb_lcd_mode;
	viaparinfo->lvds_setting_info2->display_method =
		viaparinfo->lvds_setting_info->display_method;
	viaparinfo->lvds_setting_info2->lcd_mode =
		viaparinfo->lvds_setting_info->lcd_mode;
}