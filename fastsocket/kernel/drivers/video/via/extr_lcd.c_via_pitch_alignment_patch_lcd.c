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
struct lvds_setting_information {int h_active; int bpp; scalar_t__ iga_path; } ;
struct lvds_chip_information {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR13 ; 
 int /*<<< orphan*/  CR35 ; 
 int /*<<< orphan*/  CR65 ; 
 int /*<<< orphan*/  CR66 ; 
 int /*<<< orphan*/  CR67 ; 
 scalar_t__ IGA2 ; 
 int /*<<< orphan*/  VIACR ; 
 int viafb_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void via_pitch_alignment_patch_lcd(
	struct lvds_setting_information *plvds_setting_info,
				   struct lvds_chip_information
				   *plvds_chip_info)
{
	unsigned char cr13, cr35, cr65, cr66, cr67;
	unsigned long dwScreenPitch = 0;
	unsigned long dwPitch;

	dwPitch = plvds_setting_info->h_active * (plvds_setting_info->bpp >> 3);
	if (dwPitch & 0x1F) {
		dwScreenPitch = ((dwPitch + 31) & ~31) >> 3;
		if (plvds_setting_info->iga_path == IGA2) {
			if (plvds_setting_info->bpp > 8) {
				cr66 = (unsigned char)(dwScreenPitch & 0xFF);
				viafb_write_reg(CR66, VIACR, cr66);
				cr67 = viafb_read_reg(VIACR, CR67) & 0xFC;
				cr67 |=
				    (unsigned
				     char)((dwScreenPitch & 0x300) >> 8);
				viafb_write_reg(CR67, VIACR, cr67);
			}

			/* Fetch Count */
			cr67 = viafb_read_reg(VIACR, CR67) & 0xF3;
			cr67 |= (unsigned char)((dwScreenPitch & 0x600) >> 7);
			viafb_write_reg(CR67, VIACR, cr67);
			cr65 = (unsigned char)((dwScreenPitch >> 1) & 0xFF);
			cr65 += 2;
			viafb_write_reg(CR65, VIACR, cr65);
		} else {
			if (plvds_setting_info->bpp > 8) {
				cr13 = (unsigned char)(dwScreenPitch & 0xFF);
				viafb_write_reg(CR13, VIACR, cr13);
				cr35 = viafb_read_reg(VIACR, CR35) & 0x1F;
				cr35 |=
				    (unsigned
				     char)((dwScreenPitch & 0x700) >> 3);
				viafb_write_reg(CR35, VIACR, cr35);
			}
		}
	}
}