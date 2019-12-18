#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct internal_reloc {size_t r_symndx; } ;
struct coff_final_link_info {int* sym_indices; scalar_t__ internal_relocs; TYPE_2__* section_info; TYPE_1__* info; int /*<<< orphan*/  external_relocs; } ;
struct TYPE_12__ {TYPE_4__* sections; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_13__ {int flags; int reloc_count; TYPE_7__* output_section; struct TYPE_13__* next; } ;
typedef  TYPE_4__ asection ;
struct TYPE_14__ {size_t target_index; scalar_t__ reloc_count; } ;
struct TYPE_11__ {scalar_t__ relocs; } ;
struct TYPE_10__ {scalar_t__ relocatable; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HAS_SYMS ; 
 int SEC_RELOC ; 
 struct internal_reloc* _bfd_coff_read_internal_relocs (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_7__* bfd_abs_section_ptr ; 
 int bfd_get_file_flags (TYPE_3__*) ; 

__attribute__((used)) static void
mark_relocs (struct coff_final_link_info *finfo, bfd *input_bfd)
{
  asection * a;

  if ((bfd_get_file_flags (input_bfd) & HAS_SYMS) == 0)
    return;

  for (a = input_bfd->sections; a != (asection *) NULL; a = a->next)
    {
      struct internal_reloc *	internal_relocs;
      struct internal_reloc *	irel;
      struct internal_reloc *	irelend;

      if ((a->flags & SEC_RELOC) == 0 || a->reloc_count  < 1)
	continue;
      /* Don't mark relocs in excluded sections.  */
      if (a->output_section == bfd_abs_section_ptr)
	continue;

      /* Read in the relocs.  */
      internal_relocs = _bfd_coff_read_internal_relocs
	(input_bfd, a, FALSE,
	 finfo->external_relocs,
	 finfo->info->relocatable,
	 (finfo->info->relocatable
	  ? (finfo->section_info[ a->output_section->target_index ].relocs + a->output_section->reloc_count)
	  : finfo->internal_relocs)
	);

      if (internal_relocs == NULL)
	continue;

      irel     = internal_relocs;
      irelend  = irel + a->reloc_count;

      /* Place a mark in the sym_indices array (whose entries have
	 been initialised to 0) for all of the symbols that are used
	 in the relocation table.  This will then be picked up in the
	 skip/don't-skip pass.  */
      for (; irel < irelend; irel++)
	finfo->sym_indices[ irel->r_symndx ] = -1;
    }
}