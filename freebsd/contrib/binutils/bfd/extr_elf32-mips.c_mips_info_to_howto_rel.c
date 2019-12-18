#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {int /*<<< orphan*/  (* elf_backend_mips_rtype_to_howto ) (unsigned int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int /*<<< orphan*/  addend; TYPE_1__** sym_ptr_ptr; int /*<<< orphan*/  howto; } ;
typedef  TYPE_2__ arelent ;
struct TYPE_8__ {int /*<<< orphan*/  r_info; } ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_3__ Elf_Internal_Rela ;

/* Variables and functions */
 int BSF_SECTION_SYM ; 
 unsigned int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ R_MIPS_GPREL16 ; 
 scalar_t__ R_MIPS_LITERAL ; 
 int /*<<< orphan*/  elf_gp (int /*<<< orphan*/ *) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_info_to_howto_rel (bfd *abfd, arelent *cache_ptr, Elf_Internal_Rela *dst)
{
  const struct elf_backend_data *bed;
  unsigned int r_type;

  r_type = ELF32_R_TYPE (dst->r_info);
  bed = get_elf_backend_data (abfd);
  cache_ptr->howto = bed->elf_backend_mips_rtype_to_howto (r_type, FALSE);

  /* The addend for a GPREL16 or LITERAL relocation comes from the GP
     value for the object file.  We get the addend now, rather than
     when we do the relocation, because the symbol manipulations done
     by the linker may cause us to lose track of the input BFD.  */
  if (((*cache_ptr->sym_ptr_ptr)->flags & BSF_SECTION_SYM) != 0
      && (r_type == (unsigned int) R_MIPS_GPREL16
	  || r_type == (unsigned int) R_MIPS_LITERAL))
    cache_ptr->addend = elf_gp (abfd);
}