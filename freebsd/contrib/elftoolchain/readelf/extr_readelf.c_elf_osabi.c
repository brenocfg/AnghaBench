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
typedef  int /*<<< orphan*/  s_abi ;

/* Variables and functions */
#define  ELFOSABI_86OPEN 146 
#define  ELFOSABI_AIX 145 
#define  ELFOSABI_ARM 144 
#define  ELFOSABI_ARM_AEABI 143 
#define  ELFOSABI_CLOUDABI 142 
#define  ELFOSABI_FREEBSD 141 
#define  ELFOSABI_GNU 140 
#define  ELFOSABI_HPUX 139 
#define  ELFOSABI_HURD 138 
#define  ELFOSABI_IRIX 137 
#define  ELFOSABI_MODESTO 136 
#define  ELFOSABI_NETBSD 135 
#define  ELFOSABI_NONE 134 
#define  ELFOSABI_NSK 133 
#define  ELFOSABI_OPENBSD 132 
#define  ELFOSABI_OPENVMS 131 
#define  ELFOSABI_SOLARIS 130 
#define  ELFOSABI_STANDALONE 129 
#define  ELFOSABI_TRU64 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
elf_osabi(unsigned int abi)
{
	static char s_abi[32];

	switch(abi) {
	case ELFOSABI_NONE: return "NONE";
	case ELFOSABI_HPUX: return "HPUX";
	case ELFOSABI_NETBSD: return "NetBSD";
	case ELFOSABI_GNU: return "GNU";
	case ELFOSABI_HURD: return "HURD";
	case ELFOSABI_86OPEN: return "86OPEN";
	case ELFOSABI_SOLARIS: return "Solaris";
	case ELFOSABI_AIX: return "AIX";
	case ELFOSABI_IRIX: return "IRIX";
	case ELFOSABI_FREEBSD: return "FreeBSD";
	case ELFOSABI_TRU64: return "TRU64";
	case ELFOSABI_MODESTO: return "MODESTO";
	case ELFOSABI_OPENBSD: return "OpenBSD";
	case ELFOSABI_OPENVMS: return "OpenVMS";
	case ELFOSABI_NSK: return "NSK";
	case ELFOSABI_CLOUDABI: return "CloudABI";
	case ELFOSABI_ARM_AEABI: return "ARM EABI";
	case ELFOSABI_ARM: return "ARM";
	case ELFOSABI_STANDALONE: return "StandAlone";
	default:
		snprintf(s_abi, sizeof(s_abi), "<unknown: %#x>", abi);
		return (s_abi);
	}
}