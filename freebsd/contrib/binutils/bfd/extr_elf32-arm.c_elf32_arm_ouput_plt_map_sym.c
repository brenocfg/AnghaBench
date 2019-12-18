#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct elf32_arm_link_hash_table {int dummy; } ;
struct TYPE_8__ {TYPE_5__* sec; int /*<<< orphan*/  finfo; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,char const*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  sec_shndx; int /*<<< orphan*/  info; } ;
typedef  TYPE_2__ output_arch_syminfo ;
typedef  enum map_symbol_type { ____Placeholder_map_symbol_type } map_symbol_type ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_10__ {scalar_t__ output_offset; TYPE_1__* output_section; } ;
struct TYPE_9__ {int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_info; scalar_t__ st_other; scalar_t__ st_size; scalar_t__ st_value; } ;
struct TYPE_7__ {scalar_t__ vma; } ;
typedef  TYPE_3__ Elf_Internal_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_ST_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STB_LOCAL ; 
 int /*<<< orphan*/  STT_NOTYPE ; 
 int /*<<< orphan*/  TRUE ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elf32_arm_ouput_plt_map_sym (output_arch_syminfo *osi,
			     enum map_symbol_type type,
			     bfd_vma offset)
{
  static const char *names[3] = {"$a", "$t", "$d"};
  struct elf32_arm_link_hash_table *htab;
  Elf_Internal_Sym sym;

  htab = elf32_arm_hash_table (osi->info);
  sym.st_value = osi->sec->output_section->vma
		 + osi->sec->output_offset
		 + offset;
  sym.st_size = 0;
  sym.st_other = 0;
  sym.st_info = ELF_ST_INFO (STB_LOCAL, STT_NOTYPE);
  sym.st_shndx = osi->sec_shndx;
  if (!osi->func (osi->finfo, names[type], &sym, osi->sec, NULL))
    return FALSE;
  return TRUE;
}