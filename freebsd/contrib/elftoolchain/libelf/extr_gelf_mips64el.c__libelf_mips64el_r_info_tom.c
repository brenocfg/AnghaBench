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
_libelf_mips64el_r_info_tom(Elf64_Xword r_info)
{
	Elf64_Xword new_info;
	uint8_t ssym, type3, type2, type;

	ssym = r_info >> 32;
	type3 = r_info >> 40;
	type2 = r_info >> 48;
	type = r_info >> 56;
	new_info = (r_info & 0xffffffff) << 32;
	new_info |= (Elf64_Xword)ssym << 24;
	new_info |= (Elf64_Xword)type3 << 16;
	new_info |= (Elf64_Xword)type2 << 8;
	new_info |= (Elf64_Xword)type;
	return (new_info);
}