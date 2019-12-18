#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_3__* section; } ;
struct TYPE_18__ {TYPE_4__ def; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_5__ u; } ;
struct TYPE_14__ {struct plt_entry* plist; } ;
struct TYPE_20__ {int dynindx; TYPE_6__ root; TYPE_1__ plt; } ;
struct ppc_link_hash_entry {TYPE_7__ elf; struct ppc_link_hash_entry* oh; scalar_t__ is_func_descriptor; } ;
struct TYPE_15__ {scalar_t__ offset; } ;
struct plt_entry {scalar_t__ addend; TYPE_2__ plt; struct plt_entry* next; } ;
typedef  enum ppc_stub_type { ____Placeholder_ppc_stub_type } ppc_stub_type ;
typedef  enum elf_ppc64_reloc_type { ____Placeholder_elf_ppc64_reloc_type } elf_ppc64_reloc_type ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_22__ {scalar_t__ output_offset; TYPE_8__* output_section; } ;
typedef  TYPE_9__ asection ;
struct TYPE_21__ {scalar_t__ vma; } ;
struct TYPE_16__ {int /*<<< orphan*/ * output_section; } ;
struct TYPE_13__ {scalar_t__ r_addend; scalar_t__ r_offset; int /*<<< orphan*/  r_info; } ;
typedef  TYPE_10__ Elf_Internal_Rela ;

/* Variables and functions */
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int R_PPC64_REL24 ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 int ppc_stub_long_branch ; 
 int ppc_stub_none ; 
 int ppc_stub_plt_call ; 

__attribute__((used)) static inline enum ppc_stub_type
ppc_type_of_stub (asection *input_sec,
		  const Elf_Internal_Rela *rel,
		  struct ppc_link_hash_entry **hash,
		  bfd_vma destination)
{
  struct ppc_link_hash_entry *h = *hash;
  bfd_vma location;
  bfd_vma branch_offset;
  bfd_vma max_branch_offset;
  enum elf_ppc64_reloc_type r_type;

  if (h != NULL)
    {
      struct ppc_link_hash_entry *fdh = h;
      if (fdh->oh != NULL
	  && fdh->oh->is_func_descriptor)
	fdh = fdh->oh;

      if (fdh->elf.dynindx != -1)
	{
	  struct plt_entry *ent;

	  for (ent = fdh->elf.plt.plist; ent != NULL; ent = ent->next)
	    if (ent->addend == rel->r_addend
		&& ent->plt.offset != (bfd_vma) -1)
	      {
		*hash = fdh;
		return ppc_stub_plt_call;
	      }
	}

      /* Here, we know we don't have a plt entry.  If we don't have a
	 either a defined function descriptor or a defined entry symbol
	 in a regular object file, then it is pointless trying to make
	 any other type of stub.  */
      if (!((fdh->elf.root.type == bfd_link_hash_defined
	    || fdh->elf.root.type == bfd_link_hash_defweak)
	    && fdh->elf.root.u.def.section->output_section != NULL)
	  && !((h->elf.root.type == bfd_link_hash_defined
		|| h->elf.root.type == bfd_link_hash_defweak)
	       && h->elf.root.u.def.section->output_section != NULL))
	return ppc_stub_none;
    }

  /* Determine where the call point is.  */
  location = (input_sec->output_offset
	      + input_sec->output_section->vma
	      + rel->r_offset);

  branch_offset = destination - location;
  r_type = ELF64_R_TYPE (rel->r_info);

  /* Determine if a long branch stub is needed.  */
  max_branch_offset = 1 << 25;
  if (r_type != R_PPC64_REL24)
    max_branch_offset = 1 << 15;

  if (branch_offset + max_branch_offset >= 2 * max_branch_offset)
    /* We need a stub.  Figure out whether a long_branch or plt_branch
       is needed later.  */
    return ppc_stub_long_branch;

  return ppc_stub_none;
}