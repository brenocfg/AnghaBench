#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ link; } ;
struct TYPE_10__ {TYPE_1__ i; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__ u; } ;
struct TYPE_12__ {TYPE_3__ root; } ;
struct alpha_elf_link_hash_entry {struct alpha_elf_got_entry* got_entries; TYPE_4__ root; } ;
struct alpha_elf_got_entry {scalar_t__ use_count; scalar_t__ reloc_type; scalar_t__ addend; struct alpha_elf_got_entry* next; int /*<<< orphan*/ * gotobj; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_15__ {int total_got_size; int local_got_size; int /*<<< orphan*/ * in_got_link_next; int /*<<< orphan*/ * gotobj; struct alpha_elf_got_entry** local_got_entries; } ;
struct TYPE_13__ {int sh_info; } ;
struct TYPE_14__ {TYPE_5__ symtab_hdr; } ;
typedef  TYPE_5__ Elf_Internal_Shdr ;

/* Variables and functions */
 int NUM_SHDR_ENTRIES (TYPE_5__*) ; 
 struct alpha_elf_link_hash_entry** alpha_elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_7__* alpha_elf_tdata (int /*<<< orphan*/ *) ; 
 scalar_t__ alpha_got_entry_size (scalar_t__) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_6__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct alpha_elf_got_entry*,int,int) ; 

__attribute__((used)) static void
elf64_alpha_merge_gots (bfd *a, bfd *b)
{
  int total = alpha_elf_tdata (a)->total_got_size;
  bfd *bsub;

  /* Remember local expansion.  */
  {
    int e = alpha_elf_tdata (b)->local_got_size;
    total += e;
    alpha_elf_tdata (a)->local_got_size += e;
  }

  for (bsub = b; bsub ; bsub = alpha_elf_tdata (bsub)->in_got_link_next)
    {
      struct alpha_elf_got_entry **local_got_entries;
      struct alpha_elf_link_hash_entry **hashes;
      Elf_Internal_Shdr *symtab_hdr;
      int i, n;

      /* Let the local .got entries know they are part of a new subsegment.  */
      local_got_entries = alpha_elf_tdata (bsub)->local_got_entries;
      if (local_got_entries)
        {
	  n = elf_tdata (bsub)->symtab_hdr.sh_info;
	  for (i = 0; i < n; ++i)
	    {
	      struct alpha_elf_got_entry *ent;
	      for (ent = local_got_entries[i]; ent; ent = ent->next)
	        ent->gotobj = a;
	    }
        }

      /* Merge the global .got entries.  */
      hashes = alpha_elf_sym_hashes (bsub);
      symtab_hdr = &elf_tdata (bsub)->symtab_hdr;

      n = NUM_SHDR_ENTRIES (symtab_hdr) - symtab_hdr->sh_info;
      for (i = 0; i < n; ++i)
        {
	  struct alpha_elf_got_entry *ae, *be, **pbe, **start;
	  struct alpha_elf_link_hash_entry *h;

	  h = hashes[i];
	  while (h->root.root.type == bfd_link_hash_indirect
	         || h->root.root.type == bfd_link_hash_warning)
	    h = (struct alpha_elf_link_hash_entry *)h->root.root.u.i.link;

	  pbe = start = &h->got_entries;
	  while ((be = *pbe) != NULL)
	    {
	      if (be->use_count == 0)
	        {
		  *pbe = be->next;
		  memset (be, 0xa5, sizeof (*be));
		  goto kill;
	        }
	      if (be->gotobj != b)
	        goto next;

	      for (ae = *start; ae ; ae = ae->next)
	        if (ae->gotobj == a
		    && ae->reloc_type == be->reloc_type
		    && ae->addend == be->addend)
		  {
		    ae->flags |= be->flags;
		    ae->use_count += be->use_count;
		    *pbe = be->next;
		    memset (be, 0xa5, sizeof (*be));
		    goto kill;
		  }
	      be->gotobj = a;
	      total += alpha_got_entry_size (be->reloc_type);

	    next:;
	      pbe = &be->next;
	    kill:;
	    }
        }

      alpha_elf_tdata (bsub)->gotobj = a;
    }
  alpha_elf_tdata (a)->total_got_size = total;

  /* Merge the two in_got chains.  */
  {
    bfd *next;

    bsub = a;
    while ((next = alpha_elf_tdata (bsub)->in_got_link_next) != NULL)
      bsub = next;

    alpha_elf_tdata (bsub)->in_got_link_next = b;
  }
}