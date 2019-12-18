#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ value; TYPE_7__* section; } ;
struct TYPE_11__ {scalar_t__ link; } ;
struct TYPE_13__ {TYPE_2__ def; TYPE_1__ i; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_3__ u; } ;
struct elf_link_hash_entry {scalar_t__ size; TYPE_6__* vtable; TYPE_4__ root; } ;
struct elf_backend_data {TYPE_5__* s; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_17__ {int reloc_count; int /*<<< orphan*/  owner; } ;
typedef  TYPE_7__ asection ;
struct TYPE_18__ {scalar_t__ r_offset; scalar_t__ r_info; scalar_t__ r_addend; } ;
struct TYPE_16__ {scalar_t__ size; scalar_t__* used; int /*<<< orphan*/ * parent; } ;
struct TYPE_15__ {unsigned int log_file_align; int int_rels_per_ext_rel; } ;
typedef  TYPE_8__ Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_8__* _bfd_elf_link_read_relocs (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
elf_gc_smash_unused_vtentry_relocs (struct elf_link_hash_entry *h, void *okp)
{
  asection *sec;
  bfd_vma hstart, hend;
  Elf_Internal_Rela *relstart, *relend, *rel;
  const struct elf_backend_data *bed;
  unsigned int log_file_align;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  /* Take care of both those symbols that do not describe vtables as
     well as those that are not loaded.  */
  if (h->vtable == NULL || h->vtable->parent == NULL)
    return TRUE;

  BFD_ASSERT (h->root.type == bfd_link_hash_defined
	      || h->root.type == bfd_link_hash_defweak);

  sec = h->root.u.def.section;
  hstart = h->root.u.def.value;
  hend = hstart + h->size;

  relstart = _bfd_elf_link_read_relocs (sec->owner, sec, NULL, NULL, TRUE);
  if (!relstart)
    return *(bfd_boolean *) okp = FALSE;
  bed = get_elf_backend_data (sec->owner);
  log_file_align = bed->s->log_file_align;

  relend = relstart + sec->reloc_count * bed->s->int_rels_per_ext_rel;

  for (rel = relstart; rel < relend; ++rel)
    if (rel->r_offset >= hstart && rel->r_offset < hend)
      {
	/* If the entry is in use, do nothing.  */
	if (h->vtable->used
	    && (rel->r_offset - hstart) < h->vtable->size)
	  {
	    bfd_vma entry = (rel->r_offset - hstart) >> log_file_align;
	    if (h->vtable->used[entry])
	      continue;
	  }
	/* Otherwise, kill it.  */
	rel->r_offset = rel->r_info = rel->r_addend = 0;
      }

  return TRUE;
}