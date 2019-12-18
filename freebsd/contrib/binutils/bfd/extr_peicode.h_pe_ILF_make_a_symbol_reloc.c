#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct internal_reloc {unsigned int r_symndx; int /*<<< orphan*/  r_type; void* r_vaddr; } ;
struct bfd_symbol {int dummy; } ;
struct TYPE_5__ {int relcount; int /*<<< orphan*/  abfd; struct internal_reloc* int_reltab; TYPE_2__* reltab; } ;
typedef  TYPE_1__ pe_ILF_vars ;
typedef  void* bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;
struct TYPE_6__ {TYPE_4__* howto; struct bfd_symbol** sym_ptr_ptr; scalar_t__ addend; void* address; } ;
typedef  TYPE_2__ arelent ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ NUM_ILF_RELOCS ; 
 TYPE_4__* bfd_reloc_type_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pe_ILF_make_a_symbol_reloc (pe_ILF_vars *               vars,
			    bfd_vma                     address,
			    bfd_reloc_code_real_type    reloc,
			    struct bfd_symbol **  	sym,
			    unsigned int                sym_index)
{
  arelent * entry;
  struct internal_reloc * internal;

  entry = vars->reltab + vars->relcount;
  internal = vars->int_reltab + vars->relcount;

  entry->address     = address;
  entry->addend      = 0;
  entry->howto       = bfd_reloc_type_lookup (vars->abfd, reloc);
  entry->sym_ptr_ptr = sym;

  internal->r_vaddr  = address;
  internal->r_symndx = sym_index;
  internal->r_type   = entry->howto->type;

  vars->relcount ++;

  BFD_ASSERT (vars->relcount <= NUM_ILF_RELOCS);
}