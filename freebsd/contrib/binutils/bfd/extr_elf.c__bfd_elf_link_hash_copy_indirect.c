#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ refcount; } ;
struct TYPE_8__ {scalar_t__ refcount; } ;
struct elf_link_hash_table {int /*<<< orphan*/  dynstr; TYPE_5__ init_plt_refcount; TYPE_3__ init_got_refcount; } ;
struct TYPE_9__ {scalar_t__ refcount; } ;
struct TYPE_7__ {scalar_t__ refcount; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct elf_link_hash_entry {int dynindx; scalar_t__ dynstr_index; TYPE_4__ plt; TYPE_2__ got; TYPE_1__ root; int /*<<< orphan*/  pointer_equality_needed; int /*<<< orphan*/  needs_plt; int /*<<< orphan*/  non_got_ref; int /*<<< orphan*/  ref_regular_nonweak; int /*<<< orphan*/  ref_regular; int /*<<< orphan*/  ref_dynamic; } ;
struct bfd_link_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_elf_strtab_delref (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 struct elf_link_hash_table* elf_hash_table (struct bfd_link_info*) ; 

void
_bfd_elf_link_hash_copy_indirect (struct bfd_link_info *info,
				  struct elf_link_hash_entry *dir,
				  struct elf_link_hash_entry *ind)
{
  struct elf_link_hash_table *htab;

  /* Copy down any references that we may have already seen to the
     symbol which just became indirect.  */

  dir->ref_dynamic |= ind->ref_dynamic;
  dir->ref_regular |= ind->ref_regular;
  dir->ref_regular_nonweak |= ind->ref_regular_nonweak;
  dir->non_got_ref |= ind->non_got_ref;
  dir->needs_plt |= ind->needs_plt;
  dir->pointer_equality_needed |= ind->pointer_equality_needed;

  if (ind->root.type != bfd_link_hash_indirect)
    return;

  /* Copy over the global and procedure linkage table refcount entries.
     These may have been already set up by a check_relocs routine.  */
  htab = elf_hash_table (info);
  if (ind->got.refcount > htab->init_got_refcount.refcount)
    {
      if (dir->got.refcount < 0)
	dir->got.refcount = 0;
      dir->got.refcount += ind->got.refcount;
      ind->got.refcount = htab->init_got_refcount.refcount;
    }

  if (ind->plt.refcount > htab->init_plt_refcount.refcount)
    {
      if (dir->plt.refcount < 0)
	dir->plt.refcount = 0;
      dir->plt.refcount += ind->plt.refcount;
      ind->plt.refcount = htab->init_plt_refcount.refcount;
    }

  if (ind->dynindx != -1)
    {
      if (dir->dynindx != -1)
	_bfd_elf_strtab_delref (htab->dynstr, dir->dynstr_index);
      dir->dynindx = ind->dynindx;
      dir->dynstr_index = ind->dynstr_index;
      ind->dynindx = -1;
      ind->dynstr_index = 0;
    }
}