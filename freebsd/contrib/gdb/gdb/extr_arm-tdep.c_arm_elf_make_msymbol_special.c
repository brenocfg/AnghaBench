#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct minimal_symbol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_4__ {TYPE_1__ internal_elf_sym; } ;
typedef  TYPE_2__ elf_symbol_type ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSYMBOL_SET_SPECIAL (struct minimal_symbol*) ; 
 scalar_t__ STT_LOPROC ; 

__attribute__((used)) static void
arm_elf_make_msymbol_special(asymbol *sym, struct minimal_symbol *msym)
{
  /* Thumb symbols are of type STT_LOPROC, (synonymous with
     STT_ARM_TFUNC).  */
  if (ELF_ST_TYPE (((elf_symbol_type *)sym)->internal_elf_sym.st_info)
      == STT_LOPROC)
    MSYMBOL_SET_SPECIAL (msym);
}