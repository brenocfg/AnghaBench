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
typedef  int uint8_t ;
typedef  int Elf64_Xword ;

/* Variables and functions */

Elf64_Xword
_libelf_mips64el_r_info_tof(Elf64_Xword r_info)
{
	Elf64_Xword new_info;
	uint8_t ssym, type3, type2, type;

	ssym = r_info >> 24;
	type3 = r_info >> 16;
	type2 = r_info >> 8;
	type = r_info;
	new_info = r_info >> 32;
	new_info |= (Elf64_Xword)ssym << 32;
	new_info |= (Elf64_Xword)type3 << 40;
	new_info |= (Elf64_Xword)type2 << 48;
	new_info |= (Elf64_Xword)type << 56;
	return (new_info);
}