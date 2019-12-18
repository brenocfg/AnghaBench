#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct spu_link_hash_table {scalar_t__ num_overlays; int /*<<< orphan*/  non_overlay_stubs; } ;
typedef  int bfd_boolean ;
struct TYPE_5__ {int /*<<< orphan*/ * output_section; } ;
typedef  TYPE_1__ asection ;
struct TYPE_6__ {scalar_t__ ovl_index; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 TYPE_2__* spu_elf_section_data (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static bfd_boolean
needs_ovl_stub (const char *sym_name,
		asection *sym_sec,
		asection *input_section,
		struct spu_link_hash_table *htab,
		bfd_boolean is_branch)
{
  if (htab->num_overlays == 0)
    return FALSE;

  if (sym_sec == NULL
      || sym_sec->output_section == NULL
      || spu_elf_section_data (sym_sec->output_section) == NULL)
    return FALSE;

  /* setjmp always goes via an overlay stub, because then the return
     and hence the longjmp goes via __ovly_return.  That magically
     makes setjmp/longjmp between overlays work.  */
  if (strncmp (sym_name, "setjmp", 6) == 0
      && (sym_name[6] == '\0' || sym_name[6] == '@'))
    return TRUE;

  /* Usually, symbols in non-overlay sections don't need stubs.  */
  if (spu_elf_section_data (sym_sec->output_section)->ovl_index == 0
      && !htab->non_overlay_stubs)
    return FALSE;

  /* A reference from some other section to a symbol in an overlay
     section needs a stub.  */
  if (spu_elf_section_data (sym_sec->output_section)->ovl_index
       != spu_elf_section_data (input_section->output_section)->ovl_index)
    return TRUE;

  /* If this insn isn't a branch then we are possibly taking the
     address of a function and passing it out somehow.  */
  return !is_branch;
}