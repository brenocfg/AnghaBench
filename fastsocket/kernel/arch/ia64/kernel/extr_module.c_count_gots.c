#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  r_info; } ;
typedef  TYPE_1__ Elf64_Rela ;

/* Variables and functions */
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_IA64_LTOFF22 136 
#define  R_IA64_LTOFF22X 135 
#define  R_IA64_LTOFF64I 134 
#define  R_IA64_LTOFF_FPTR22 133 
#define  R_IA64_LTOFF_FPTR32LSB 132 
#define  R_IA64_LTOFF_FPTR32MSB 131 
#define  R_IA64_LTOFF_FPTR64I 130 
#define  R_IA64_LTOFF_FPTR64LSB 129 
#define  R_IA64_LTOFF_FPTR64MSB 128 
 int /*<<< orphan*/  duplicate_reloc (TYPE_1__ const*,unsigned int) ; 

__attribute__((used)) static unsigned int
count_gots (const Elf64_Rela *rela, unsigned int num)
{
	unsigned int i, ret = 0;

	/* Sure, this is order(n^2), but it's usually short, and not
           time critical */
	for (i = 0; i < num; i++) {
		switch (ELF64_R_TYPE(rela[i].r_info)) {
		      case R_IA64_LTOFF22:
		      case R_IA64_LTOFF22X:
		      case R_IA64_LTOFF64I:
		      case R_IA64_LTOFF_FPTR22:
		      case R_IA64_LTOFF_FPTR64I:
		      case R_IA64_LTOFF_FPTR32MSB:
		      case R_IA64_LTOFF_FPTR32LSB:
		      case R_IA64_LTOFF_FPTR64MSB:
		      case R_IA64_LTOFF_FPTR64LSB:
			if (!duplicate_reloc(rela, i))
				ret++;
			break;
		}
	}
	return ret;
}