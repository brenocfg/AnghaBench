#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int arch; int mode; } ;
typedef  TYPE_1__ cs_struct ;

/* Variables and functions */
#define  CS_ARCH_ARM 140 
#define  CS_ARCH_ARM64 139 
#define  CS_ARCH_EVM 138 
#define  CS_ARCH_M680X 137 
#define  CS_ARCH_M68K 136 
#define  CS_ARCH_MIPS 135 
#define  CS_ARCH_MOS65XX 134 
#define  CS_ARCH_PPC 133 
#define  CS_ARCH_SPARC 132 
#define  CS_ARCH_SYSZ 131 
#define  CS_ARCH_TMS320C64X 130 
#define  CS_ARCH_X86 129 
#define  CS_ARCH_XCORE 128 
 int CS_MODE_THUMB ; 

__attribute__((used)) static uint8_t skipdata_size(cs_struct *handle)
{
	switch(handle->arch) {
		default:
			// should never reach
			return (uint8_t)-1;
		case CS_ARCH_ARM:
			// skip 2 bytes on Thumb mode.
			if (handle->mode & CS_MODE_THUMB)
				return 2;
			// otherwise, skip 4 bytes
			return 4;
		case CS_ARCH_ARM64:
		case CS_ARCH_MIPS:
		case CS_ARCH_PPC:
		case CS_ARCH_SPARC:
			// skip 4 bytes
			return 4;
		case CS_ARCH_SYSZ:
			// SystemZ instruction's length can be 2, 4 or 6 bytes,
			// so we just skip 2 bytes
			return 2;
		case CS_ARCH_X86:
			// X86 has no restriction on instruction alignment
			return 1;
		case CS_ARCH_XCORE:
			// XCore instruction's length can be 2 or 4 bytes,
			// so we just skip 2 bytes
			return 2;
		case CS_ARCH_M68K:
			// M68K has 2 bytes instruction alignment but contain multibyte instruction so we skip 2 bytes
			return 2;
		case CS_ARCH_TMS320C64X:
			// TMS320C64x alignment is 4.
			return 4;
		case CS_ARCH_M680X:
			// M680X alignment is 1.
			return 1;
		case CS_ARCH_EVM:
			// EVM alignment is 1.
			return 1;
		case CS_ARCH_MOS65XX:
			// MOS65XX alignment is 1.
			return 1;
	}
}