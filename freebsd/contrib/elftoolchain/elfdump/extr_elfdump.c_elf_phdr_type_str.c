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
typedef  int /*<<< orphan*/  s_type ;

/* Variables and functions */
#define  PT_DYNAMIC 141 
#define  PT_GNU_EH_FRAME 140 
#define  PT_GNU_RELRO 139 
#define  PT_GNU_STACK 138 
#define  PT_INTERP 137 
#define  PT_LOAD 136 
#define  PT_NOTE 135 
#define  PT_NULL 134 
#define  PT_OPENBSD_BOOTDATA 133 
#define  PT_OPENBSD_RANDOMIZE 132 
#define  PT_OPENBSD_WXNEEDED 131 
#define  PT_PHDR 130 
#define  PT_SHLIB 129 
#define  PT_TLS 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
elf_phdr_type_str(unsigned int type)
{
	static char s_type[32];

	switch (type) {
	case PT_NULL:			return "PT_NULL";
	case PT_LOAD:			return "PT_LOAD";
	case PT_DYNAMIC:		return "PT_DYNAMIC";
	case PT_INTERP:			return "PT_INTERP";
	case PT_NOTE:			return "PT_NOTE";
	case PT_SHLIB:			return "PT_SHLIB";
	case PT_PHDR:			return "PT_PHDR";
	case PT_TLS:			return "PT_TLS";
	case PT_GNU_EH_FRAME:		return "PT_GNU_EH_FRAME";
	case PT_GNU_STACK:		return "PT_GNU_STACK";
	case PT_GNU_RELRO:		return "PT_GNU_RELRO";
	case PT_OPENBSD_RANDOMIZE:	return "PT_OPENBSD_RANDOMIZE";
	case PT_OPENBSD_WXNEEDED:	return "PT_OPENBSD_WXNEEDED";
	case PT_OPENBSD_BOOTDATA:	return "PT_OPENBSD_BOOTDATA";
	}
	snprintf(s_type, sizeof(s_type), "<unknown: %#x>", type);
	return (s_type);
}