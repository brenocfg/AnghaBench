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
typedef  int /*<<< orphan*/  s_stype ;

/* Variables and functions */
 unsigned int ELFOSABI_FREEBSD ; 
 unsigned int ELFOSABI_GNU ; 
 unsigned int EM_SPARCV9 ; 
#define  STT_COMMON 134 
#define  STT_FILE 133 
#define  STT_FUNC 132 
 unsigned int STT_GNU_IFUNC ; 
 unsigned int STT_HIOS ; 
 unsigned int STT_HIPROC ; 
 unsigned int STT_LOOS ; 
 unsigned int STT_LOPROC ; 
#define  STT_NOTYPE 131 
#define  STT_OBJECT 130 
#define  STT_SECTION 129 
 unsigned int STT_SPARC_REGISTER ; 
#define  STT_TLS 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
st_type(unsigned int mach, unsigned int os, unsigned int stype)
{
	static char s_stype[32];

	switch (stype) {
	case STT_NOTYPE: return "NOTYPE";
	case STT_OBJECT: return "OBJECT";
	case STT_FUNC: return "FUNC";
	case STT_SECTION: return "SECTION";
	case STT_FILE: return "FILE";
	case STT_COMMON: return "COMMON";
	case STT_TLS: return "TLS";
	default:
		if (stype >= STT_LOOS && stype <= STT_HIOS) {
			if ((os == ELFOSABI_GNU || os == ELFOSABI_FREEBSD) &&
			    stype == STT_GNU_IFUNC)
				return "IFUNC";
			snprintf(s_stype, sizeof(s_stype), "OS+%#x",
			    stype - STT_LOOS);
		} else if (stype >= STT_LOPROC && stype <= STT_HIPROC) {
			if (mach == EM_SPARCV9 && stype == STT_SPARC_REGISTER)
				return "REGISTER";
			snprintf(s_stype, sizeof(s_stype), "PROC+%#x",
			    stype - STT_LOPROC);
		} else
			snprintf(s_stype, sizeof(s_stype), "<unknown: %#x>",
			    stype);
		return (s_stype);
	}
}