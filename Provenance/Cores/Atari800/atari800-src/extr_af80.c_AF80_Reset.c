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

/* Variables and functions */
 int /*<<< orphan*/  af80_attrib ; 
 int /*<<< orphan*/  af80_screen ; 
 int /*<<< orphan*/  crtreg ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ not_enable_2k_attribute_ram ; 
 scalar_t__ not_enable_2k_character_ram ; 
 scalar_t__ not_enable_80_column_output ; 
 scalar_t__ not_enable_crtc_registers ; 
 scalar_t__ not_right_cartridge_rd4_control ; 
 scalar_t__ not_rom_output_enable ; 
 scalar_t__ rom_bank_select ; 
 scalar_t__ video_bank_select ; 

void AF80_Reset(void)
{
	memset(af80_screen, 0, 0x800);
	memset(af80_attrib, 0, 0x800);
	rom_bank_select = 0;
	not_rom_output_enable = 0;
	not_right_cartridge_rd4_control = 0;
	not_enable_2k_character_ram = 0;
	not_enable_2k_attribute_ram = 0;
	not_enable_crtc_registers = 0;
	not_enable_80_column_output = 0;
	video_bank_select = 0;
	memset(crtreg, 0, 0x40);
}