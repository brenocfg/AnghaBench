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
struct TYPE_3__ {unsigned int r_addend; int /*<<< orphan*/  r_info; } ;
typedef  TYPE_1__ Elf32_Rela ;

/* Variables and functions */
 unsigned int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ R_PPC_REL24 ; 

__attribute__((used)) static unsigned int count_relocs(const Elf32_Rela *rela, unsigned int num)
{
	unsigned int i, r_info, r_addend, _count_relocs;

	_count_relocs = 0;
	r_info = 0;
	r_addend = 0;
	for (i = 0; i < num; i++)
		/* Only count 24-bit relocs, others don't need stubs */
		if (ELF32_R_TYPE(rela[i].r_info) == R_PPC_REL24 &&
		    (r_info != ELF32_R_SYM(rela[i].r_info) ||
		     r_addend != rela[i].r_addend)) {
			_count_relocs++;
			r_info = ELF32_R_SYM(rela[i].r_info);
			r_addend = rela[i].r_addend;
		}

#ifdef CONFIG_DYNAMIC_FTRACE
	_count_relocs++;	/* add one for ftrace_caller */
#endif
	return _count_relocs;
}