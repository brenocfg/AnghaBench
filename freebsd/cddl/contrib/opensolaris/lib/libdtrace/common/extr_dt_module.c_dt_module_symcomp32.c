#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ st_value; scalar_t__ st_size; scalar_t__ st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ Elf32_Sym ;

/* Variables and functions */
 scalar_t__ ELF32_ST_BIND (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF32_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STB_WEAK ; 
 scalar_t__ STT_NOTYPE ; 
 scalar_t__ dt_module_strtab ; 
 int strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
dt_module_symcomp32(const void *lp, const void *rp)
{
	Elf32_Sym *lhs = *((Elf32_Sym **)lp);
	Elf32_Sym *rhs = *((Elf32_Sym **)rp);

	if (lhs->st_value != rhs->st_value)
		return (lhs->st_value > rhs->st_value ? 1 : -1);

	if ((lhs->st_size == 0) != (rhs->st_size == 0))
		return (lhs->st_size == 0 ? 1 : -1);

	if ((ELF32_ST_TYPE(lhs->st_info) == STT_NOTYPE) !=
	    (ELF32_ST_TYPE(rhs->st_info) == STT_NOTYPE))
		return (ELF32_ST_TYPE(lhs->st_info) == STT_NOTYPE ? 1 : -1);

	if ((ELF32_ST_BIND(lhs->st_info) == STB_WEAK) !=
	    (ELF32_ST_BIND(rhs->st_info) == STB_WEAK))
		return (ELF32_ST_BIND(lhs->st_info) == STB_WEAK ? 1 : -1);

	return (strcmp(dt_module_strtab + lhs->st_name,
	    dt_module_strtab + rhs->st_name));
}