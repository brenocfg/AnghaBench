#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  abfd; } ;
typedef  TYPE_1__ pe_ILF_vars ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;
typedef  TYPE_2__* asection_ptr ;
struct TYPE_10__ {int /*<<< orphan*/  i; } ;
struct TYPE_9__ {int /*<<< orphan*/  symbol_ptr_ptr; } ;

/* Variables and functions */
 TYPE_6__* coff_section_data (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pe_ILF_make_a_symbol_reloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pe_ILF_make_a_reloc (pe_ILF_vars *             vars,
		     bfd_vma                   address,
		     bfd_reloc_code_real_type  reloc,
		     asection_ptr              sec)
{
  pe_ILF_make_a_symbol_reloc (vars, address, reloc, sec->symbol_ptr_ptr,
			      coff_section_data (vars->abfd, sec)->i);
}