#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ string; } ;
struct ppc_stub_hash_entry {scalar_t__ stub_type; scalar_t__ addend; int target_value; TYPE_9__* stub_sec; TYPE_16__* id_sec; TYPE_11__ root; TYPE_10__* target_section; TYPE_3__* h; } ;
struct ppc_link_hash_table {scalar_t__ stub_iteration; TYPE_15__* stub_group; TYPE_14__* brlt; TYPE_12__* relbrlt; int /*<<< orphan*/  stub_error; int /*<<< orphan*/  branch_hash_table; TYPE_6__* plt; } ;
struct ppc_branch_hash_entry {scalar_t__ iter; int offset; } ;
struct TYPE_27__ {int offset; } ;
struct plt_entry {scalar_t__ addend; TYPE_4__ plt; struct plt_entry* next; } ;
struct bfd_link_info {scalar_t__ emitrelocations; } ;
struct bfd_hash_entry {int dummy; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_32__ {int size; int output_offset; int reloc_count; int /*<<< orphan*/  flags; TYPE_8__* output_section; } ;
struct TYPE_31__ {int vma; } ;
struct TYPE_30__ {int vma; } ;
struct TYPE_29__ {int output_offset; TYPE_5__* output_section; } ;
struct TYPE_28__ {int vma; int /*<<< orphan*/  owner; } ;
struct TYPE_24__ {struct plt_entry* plist; } ;
struct TYPE_25__ {TYPE_1__ plt; } ;
struct TYPE_26__ {TYPE_2__ elf; } ;
struct TYPE_23__ {size_t id; } ;
struct TYPE_22__ {int toc_off; } ;
struct TYPE_21__ {int size; int reloc_count; int output_offset; TYPE_13__* output_section; int /*<<< orphan*/  flags; } ;
struct TYPE_20__ {int vma; int /*<<< orphan*/  owner; } ;
struct TYPE_19__ {int size; } ;
struct TYPE_17__ {int output_offset; size_t id; TYPE_7__* output_section; } ;
typedef  int /*<<< orphan*/  Elf64_External_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PLT_CALL_STUB_SIZE ; 
 scalar_t__ PPC_HA (int) ; 
 int /*<<< orphan*/  SEC_RELOC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  abort () ; 
 int elf_gp (int /*<<< orphan*/ ) ; 
 struct ppc_branch_hash_entry* ppc_branch_hash_lookup (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 
 scalar_t__ ppc_stub_long_branch ; 
 scalar_t__ ppc_stub_long_branch_r2off ; 
 scalar_t__ ppc_stub_plt_branch ; 
 scalar_t__ ppc_stub_plt_branch_r2off ; 
 scalar_t__ ppc_stub_plt_call ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bfd_boolean
ppc_size_one_stub (struct bfd_hash_entry *gen_entry, void *in_arg)
{
  struct ppc_stub_hash_entry *stub_entry;
  struct bfd_link_info *info;
  struct ppc_link_hash_table *htab;
  bfd_vma off;
  int size;

  /* Massage our args to the form they really have.  */
  stub_entry = (struct ppc_stub_hash_entry *) gen_entry;
  info = in_arg;

  htab = ppc_hash_table (info);

  if (stub_entry->stub_type == ppc_stub_plt_call)
    {
      struct plt_entry *ent;
      off = (bfd_vma) -1;
      for (ent = stub_entry->h->elf.plt.plist; ent != NULL; ent = ent->next)
	if (ent->addend == stub_entry->addend)
	  {
	    off = ent->plt.offset & ~(bfd_vma) 1;
	    break;
	  }
      if (off >= (bfd_vma) -2)
	abort ();
      off += (htab->plt->output_offset
	      + htab->plt->output_section->vma
	      - elf_gp (htab->plt->output_section->owner)
	      - htab->stub_group[stub_entry->id_sec->id].toc_off);

      size = PLT_CALL_STUB_SIZE;
      if (PPC_HA (off) == 0)
	size -= 4;
      if (PPC_HA (off + 16) != PPC_HA (off))
	size += 4;
    }
  else
    {
      /* ppc_stub_long_branch or ppc_stub_plt_branch, or their r2off
	 variants.  */
      bfd_vma r2off = 0;

      off = (stub_entry->target_value
	     + stub_entry->target_section->output_offset
	     + stub_entry->target_section->output_section->vma);
      off -= (stub_entry->stub_sec->size
	      + stub_entry->stub_sec->output_offset
	      + stub_entry->stub_sec->output_section->vma);

      /* Reset the stub type from the plt variant in case we now
	 can reach with a shorter stub.  */
      if (stub_entry->stub_type >= ppc_stub_plt_branch)
	stub_entry->stub_type += ppc_stub_long_branch - ppc_stub_plt_branch;

      size = 4;
      if (stub_entry->stub_type == ppc_stub_long_branch_r2off)
	{
	  r2off = (htab->stub_group[stub_entry->target_section->id].toc_off
		   - htab->stub_group[stub_entry->id_sec->id].toc_off);
	  size = 12;
	  if (PPC_HA (r2off) != 0)
	    size = 16;
	  off -= size - 4;
	}

      /* If the branch offset if too big, use a ppc_stub_plt_branch.  */
      if (off + (1 << 25) >= (bfd_vma) (1 << 26))
	{
	  struct ppc_branch_hash_entry *br_entry;
	  unsigned int indx;

	  br_entry = ppc_branch_hash_lookup (&htab->branch_hash_table,
					     stub_entry->root.string + 9,
					     TRUE, FALSE);
	  if (br_entry == NULL)
	    {
	      (*_bfd_error_handler) (_("can't build branch stub `%s'"),
				     stub_entry->root.string);
	      htab->stub_error = TRUE;
	      return FALSE;
	    }

	  if (br_entry->iter != htab->stub_iteration)
	    {
	      br_entry->iter = htab->stub_iteration;
	      br_entry->offset = htab->brlt->size;
	      htab->brlt->size += 8;

	      if (htab->relbrlt != NULL)
		htab->relbrlt->size += sizeof (Elf64_External_Rela);
	      else if (info->emitrelocations)
		{
		  htab->brlt->reloc_count += 1;
		  htab->brlt->flags |= SEC_RELOC;
		}
	    }

	  stub_entry->stub_type += ppc_stub_plt_branch - ppc_stub_long_branch;
	  off = (br_entry->offset
		 + htab->brlt->output_offset
		 + htab->brlt->output_section->vma
		 - elf_gp (htab->brlt->output_section->owner)
		 - htab->stub_group[stub_entry->id_sec->id].toc_off);

	  indx = off;
	  if (stub_entry->stub_type != ppc_stub_plt_branch_r2off)
	    {
	      size = 12;
	      if (PPC_HA (indx) != 0)
		size = 16;
	    }
	  else
	    {
	      size = 20;
	      if (PPC_HA (indx) != 0)
		size += 4;

	      if (PPC_HA (r2off) != 0)
		size += 4;
	    }
	}
      else if (info->emitrelocations)
	{
	  stub_entry->stub_sec->reloc_count += 1;
	  stub_entry->stub_sec->flags |= SEC_RELOC;
	}
    }

  stub_entry->stub_sec->size += size;
  return TRUE;
}