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
struct device_t {scalar_t__ lcd_mode; scalar_t__ lcd_panel_id; int xres1; int yres1; scalar_t__ bpp; scalar_t__ bpp1; scalar_t__ refresh; scalar_t__ refresh1; scalar_t__ samm; int /*<<< orphan*/  primary_dev; scalar_t__ lcd_dsp_cent; scalar_t__ lcd; scalar_t__ dvi; scalar_t__ crt; } ;
struct TYPE_4__ {TYPE_1__* lvds_setting_info; } ;
struct TYPE_3__ {void* lcd_mode; void* display_method; } ;

/* Variables and functions */
 int CRT_Device ; 
 int DVI_Device ; 
 void* LCD_CENTERING ; 
 int LCD_Device ; 
 void* LCD_EXPANDSION ; 
 void* LCD_OPENLDI ; 
 scalar_t__ LCD_PANEL_ID_MAXIMUM ; 
 scalar_t__ LCD_SPWG ; 
 int None_Device ; 
 scalar_t__ STATE_OFF ; 
 scalar_t__ STATE_ON ; 
 int /*<<< orphan*/  check_available_device_to_enable (int) ; 
 scalar_t__ viafb_LCD_ON ; 
 scalar_t__ viafb_SAMM_ON ; 
 scalar_t__ viafb_bpp ; 
 scalar_t__ viafb_bpp1 ; 
 int /*<<< orphan*/  viafb_init_lcd_size () ; 
 void* viafb_lcd_dsp_method ; 
 void* viafb_lcd_mode ; 
 scalar_t__ viafb_lcd_panel_id ; 
 int /*<<< orphan*/  viafb_primary_dev ; 
 scalar_t__ viafb_refresh ; 
 scalar_t__ viafb_refresh1 ; 
 int /*<<< orphan*/  viafb_second_offset ; 
 int viafb_second_xres ; 
 int viafb_second_yres ; 
 int /*<<< orphan*/  viafb_set_iga_path () ; 
 int /*<<< orphan*/  viafb_set_primary_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_set_secondary_address (int /*<<< orphan*/ ) ; 
 TYPE_2__* viaparinfo ; 

__attribute__((used)) static void viafb_set_device(struct device_t active_dev)
{
	/* Check available device to enable: */
	int device_id = None_Device;
	if (active_dev.crt)
		device_id |= CRT_Device;
	if (active_dev.dvi)
		device_id |= DVI_Device;
	if (active_dev.lcd)
		device_id |= LCD_Device;

	check_available_device_to_enable(device_id);

	/* Check property of LCD: */
	if (viafb_LCD_ON) {
		if (active_dev.lcd_dsp_cent) {
			viaparinfo->lvds_setting_info->display_method =
				viafb_lcd_dsp_method = LCD_CENTERING;
		} else {
			viaparinfo->lvds_setting_info->display_method =
				viafb_lcd_dsp_method = LCD_EXPANDSION;
		}

		if (active_dev.lcd_mode == LCD_SPWG) {
			viaparinfo->lvds_setting_info->lcd_mode =
				viafb_lcd_mode = LCD_SPWG;
		} else {
			viaparinfo->lvds_setting_info->lcd_mode =
				viafb_lcd_mode = LCD_OPENLDI;
		}

		if (active_dev.lcd_panel_id <= LCD_PANEL_ID_MAXIMUM) {
			viafb_lcd_panel_id = active_dev.lcd_panel_id;
			viafb_init_lcd_size();
		}
	}

	/* Check property of mode: */
	if (!active_dev.xres1)
		viafb_second_xres = 640;
	else
		viafb_second_xres = active_dev.xres1;
	if (!active_dev.yres1)
		viafb_second_yres = 480;
	else
		viafb_second_yres = active_dev.yres1;
	if (active_dev.bpp != 0)
		viafb_bpp = active_dev.bpp;
	if (active_dev.bpp1 != 0)
		viafb_bpp1 = active_dev.bpp1;
	if (active_dev.refresh != 0)
		viafb_refresh = active_dev.refresh;
	if (active_dev.refresh1 != 0)
		viafb_refresh1 = active_dev.refresh1;
	if ((active_dev.samm == STATE_OFF) || (active_dev.samm == STATE_ON))
		viafb_SAMM_ON = active_dev.samm;
	viafb_primary_dev = active_dev.primary_dev;

	viafb_set_primary_address(0);
	viafb_set_secondary_address(viafb_SAMM_ON ? viafb_second_offset : 0);
	viafb_set_iga_path();
}