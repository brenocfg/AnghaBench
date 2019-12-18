#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ string_table; scalar_t__ int_reltab; scalar_t__ relcount; int /*<<< orphan*/  reltab; int /*<<< orphan*/  abfd; } ;
typedef  TYPE_1__ pe_ILF_vars ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  TYPE_2__* asection_ptr ;
struct TYPE_9__ {int /*<<< orphan*/  keep_relocs; scalar_t__ relocs; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; scalar_t__ reloc_count; int /*<<< orphan*/  relocation; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  SEC_RELOC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_5__* coff_section_data (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
pe_ILF_save_relocs (pe_ILF_vars * vars,
		    asection_ptr  sec)
{
  /* Make sure that there is somewhere to store the internal relocs.  */
  if (coff_section_data (vars->abfd, sec) == NULL)
    /* We should probably return an error indication here.  */
    abort ();

  coff_section_data (vars->abfd, sec)->relocs = vars->int_reltab;
  coff_section_data (vars->abfd, sec)->keep_relocs = TRUE;

  sec->relocation  = vars->reltab;
  sec->reloc_count = vars->relcount;
  sec->flags      |= SEC_RELOC;

  vars->reltab     += vars->relcount;
  vars->int_reltab += vars->relcount;
  vars->relcount   = 0;

  BFD_ASSERT ((bfd_byte *) vars->int_reltab < (bfd_byte *) vars->string_table);
}