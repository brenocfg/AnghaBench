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
typedef  int /*<<< orphan*/  s_shndx ;

/* Variables and functions */
#define  SHN_ABS 130 
#define  SHN_COMMON 129 
 unsigned int SHN_HIOS ; 
 unsigned int SHN_HIPROC ; 
 unsigned int SHN_LOOS ; 
 unsigned int SHN_LOPROC ; 
#define  SHN_UNDEF 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
st_shndx(unsigned int shndx)
{
	static char s_shndx[32];

	switch (shndx) {
	case SHN_UNDEF: return "UND";
	case SHN_ABS: return "ABS";
	case SHN_COMMON: return "COM";
	default:
		if (shndx >= SHN_LOPROC && shndx <= SHN_HIPROC)
			return "PRC";
		else if (shndx >= SHN_LOOS && shndx <= SHN_HIOS)
			return "OS";
		else
			snprintf(s_shndx, sizeof(s_shndx), "%u", shndx);
		return (s_shndx);
	}
}