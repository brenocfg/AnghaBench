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
typedef  int UWORD ;

/* Variables and functions */
 int CPU_REMEMBER_PC_STEPS ; 
 int* CPU_remember_PC ; 
 int CPU_remember_PC_curpos ; 
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int MEMORY_dGetByte (int) ; 
 int* crtreg ; 
 int /*<<< orphan*/  not_enable_2k_attribute_ram ; 
 int /*<<< orphan*/  not_enable_2k_character_ram ; 
 int /*<<< orphan*/  not_enable_crtc_registers ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ video_bank_select ; 

int AF80_D6GetByte(UWORD addr, int no_side_effects)
{
	int result = 0xff;
	if (!not_enable_2k_character_ram) {
		result = MEMORY_dGetByte(addr);
	}
	else if (!not_enable_2k_attribute_ram) {
		result = MEMORY_dGetByte(addr);
	}
	else if (!not_enable_crtc_registers) {
		if (video_bank_select == 0 ) {
			if ((addr&0xff)<0x40) {
				result = crtreg[addr&0xff];
				if ((addr&0xff) == 0x3a) {
					result = 0x01;
				}
			}
			D(printf("AF80 Read addr:%4x cpu:%4x\n", addr, CPU_remember_PC[(CPU_remember_PC_curpos-1)%CPU_REMEMBER_PC_STEPS]));
		}
	}
	return result;
}