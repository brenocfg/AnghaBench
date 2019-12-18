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
 scalar_t__ MEMORY_mem ; 
 scalar_t__ af80_attrib ; 
 scalar_t__ af80_screen ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  not_enable_2k_attribute_ram ; 
 int /*<<< orphan*/  not_enable_2k_character_ram ; 
 scalar_t__ not_enable_crtc_registers ; 
 int video_bank_select ; 

__attribute__((used)) static void update_d6(void)
{
	if (!not_enable_2k_character_ram) {
		memcpy(MEMORY_mem + 0xd600, af80_screen + (video_bank_select<<7), 0x80);
		memcpy(MEMORY_mem + 0xd680, af80_screen + (video_bank_select<<7), 0x80);
	}
	else if (!not_enable_2k_attribute_ram) {
		memcpy(MEMORY_mem + 0xd600, af80_attrib + (video_bank_select<<7), 0x80);
		memcpy(MEMORY_mem + 0xd680, af80_attrib + (video_bank_select<<7), 0x80);
	}
	else if (not_enable_crtc_registers) {
		memset(MEMORY_mem + 0xd600, 0xff, 0x100);
	}
}