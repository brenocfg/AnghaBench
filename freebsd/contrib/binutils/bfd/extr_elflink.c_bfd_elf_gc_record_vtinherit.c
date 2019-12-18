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
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ value; int /*<<< orphan*/ * section; } ;
struct TYPE_11__ {TYPE_3__ def; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_4__ u; } ;
struct elf_link_hash_entry {TYPE_7__* vtable; TYPE_5__ root; } ;
struct elf_backend_data {TYPE_1__* s; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_14__ {struct elf_link_hash_entry* parent; } ;
struct TYPE_9__ {int sh_size; scalar_t__ sh_info; } ;
struct TYPE_13__ {TYPE_2__ symtab_hdr; } ;
struct TYPE_8__ {int sizeof_sym; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_error_handler (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_7__* bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  elf_bad_symtab (int /*<<< orphan*/ *) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_6__* elf_tdata (int /*<<< orphan*/ *) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

bfd_boolean
bfd_elf_gc_record_vtinherit (bfd *abfd,
			     asection *sec,
			     struct elf_link_hash_entry *h,
			     bfd_vma offset)
{
  struct elf_link_hash_entry **sym_hashes, **sym_hashes_end;
  struct elf_link_hash_entry **search, *child;
  bfd_size_type extsymcount;
  const struct elf_backend_data *bed = get_elf_backend_data (abfd);

  /* The sh_info field of the symtab header tells us where the
     external symbols start.  We don't care about the local symbols at
     this point.  */
  extsymcount = elf_tdata (abfd)->symtab_hdr.sh_size / bed->s->sizeof_sym;
  if (!elf_bad_symtab (abfd))
    extsymcount -= elf_tdata (abfd)->symtab_hdr.sh_info;

  sym_hashes = elf_sym_hashes (abfd);
  sym_hashes_end = sym_hashes + extsymcount;

  /* Hunt down the child symbol, which is in this section at the same
     offset as the relocation.  */
  for (search = sym_hashes; search != sym_hashes_end; ++search)
    {
      if ((child = *search) != NULL
	  && (child->root.type == bfd_link_hash_defined
	      || child->root.type == bfd_link_hash_defweak)
	  && child->root.u.def.section == sec
	  && child->root.u.def.value == offset)
	goto win;
    }

  (*_bfd_error_handler) ("%B: %A+%lu: No symbol found for INHERIT",
			 abfd, sec, (unsigned long) offset);
  bfd_set_error (bfd_error_invalid_operation);
  return FALSE;

 win:
  if (!child->vtable)
    {
      child->vtable = bfd_zalloc (abfd, sizeof (*child->vtable));
      if (!child->vtable)
	return FALSE;
    }
  if (!h)
    {
      /* This *should* only be the absolute section.  It could potentially
	 be that someone has defined a non-global vtable though, which
	 would be bad.  It isn't worth paging in the local symbols to be
	 sure though; that case should simply be handled by the assembler.  */

      child->vtable->parent = (struct elf_link_hash_entry *) -1;
    }
  else
    child->vtable->parent = h;

  return TRUE;
}