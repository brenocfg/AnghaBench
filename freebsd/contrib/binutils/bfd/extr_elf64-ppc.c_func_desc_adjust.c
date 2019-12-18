#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  root; } ;
struct ppc_link_hash_table {TYPE_1__ elf; } ;
struct TYPE_12__ {scalar_t__ link; } ;
struct TYPE_13__ {int /*<<< orphan*/  value; int /*<<< orphan*/  section; } ;
struct TYPE_14__ {TYPE_2__ i; TYPE_3__ def; } ;
struct TYPE_17__ {char* string; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_4__ u; TYPE_7__ root; } ;
struct TYPE_15__ {struct plt_entry* plist; } ;
struct TYPE_19__ {int forced_local; int dynindx; int needs_plt; int /*<<< orphan*/  def_regular; int /*<<< orphan*/  other; int /*<<< orphan*/  non_got_ref; int /*<<< orphan*/  ref_regular_nonweak; int /*<<< orphan*/  ref_dynamic; int /*<<< orphan*/  ref_regular; TYPE_8__ root; scalar_t__ def_dynamic; TYPE_5__ plt; } ;
struct ppc_link_hash_entry {int is_func_descriptor; TYPE_9__ elf; struct ppc_link_hash_entry* oh; scalar_t__ fake; int /*<<< orphan*/  is_func; scalar_t__ was_undefined; } ;
struct TYPE_16__ {scalar_t__ refcount; } ;
struct plt_entry {TYPE_6__ plt; struct plt_entry* next; } ;
struct elf_link_hash_entry {int dummy; } ;
struct bfd_link_info {scalar_t__ shared; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_boolean ;

/* Variables and functions */
 scalar_t__ ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 scalar_t__ STV_DEFAULT ; 
 int TRUE ; 
 int /*<<< orphan*/  _bfd_elf_link_hash_hide_symbol (struct bfd_link_info*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (struct bfd_link_info*,TYPE_9__*) ; 
 int /*<<< orphan*/  bfd_link_add_undef (int /*<<< orphan*/ *,TYPE_8__*) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_undefined ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 struct ppc_link_hash_entry* get_fdh (struct ppc_link_hash_entry*,struct ppc_link_hash_table*) ; 
 int /*<<< orphan*/ * get_opd_info (int /*<<< orphan*/ ) ; 
 struct ppc_link_hash_entry* make_fdh (struct bfd_link_info*,struct ppc_link_hash_entry*) ; 
 int /*<<< orphan*/  move_plt_plist (struct ppc_link_hash_entry*,struct ppc_link_hash_entry*) ; 
 scalar_t__ opd_entry_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
func_desc_adjust (struct elf_link_hash_entry *h, void *inf)
{
  struct bfd_link_info *info;
  struct ppc_link_hash_table *htab;
  struct plt_entry *ent;
  struct ppc_link_hash_entry *fh;
  struct ppc_link_hash_entry *fdh;
  bfd_boolean force_local;

  fh = (struct ppc_link_hash_entry *) h;
  if (fh->elf.root.type == bfd_link_hash_indirect)
    return TRUE;

  if (fh->elf.root.type == bfd_link_hash_warning)
    fh = (struct ppc_link_hash_entry *) fh->elf.root.u.i.link;

  info = inf;
  htab = ppc_hash_table (info);

  /* Resolve undefined references to dot-symbols as the value
     in the function descriptor, if we have one in a regular object.
     This is to satisfy cases like ".quad .foo".  Calls to functions
     in dynamic objects are handled elsewhere.  */
  if (fh->elf.root.type == bfd_link_hash_undefweak
      && fh->was_undefined
      && (fh->oh->elf.root.type == bfd_link_hash_defined
	  || fh->oh->elf.root.type == bfd_link_hash_defweak)
      && get_opd_info (fh->oh->elf.root.u.def.section) != NULL
      && opd_entry_value (fh->oh->elf.root.u.def.section,
			  fh->oh->elf.root.u.def.value,
			  &fh->elf.root.u.def.section,
			  &fh->elf.root.u.def.value) != (bfd_vma) -1)
    {
      fh->elf.root.type = fh->oh->elf.root.type;
      fh->elf.forced_local = 1;
      fh->elf.def_regular = fh->oh->elf.def_regular;
      fh->elf.def_dynamic = fh->oh->elf.def_dynamic;
    }

  /* If this is a function code symbol, transfer dynamic linking
     information to the function descriptor symbol.  */
  if (!fh->is_func)
    return TRUE;

  for (ent = fh->elf.plt.plist; ent != NULL; ent = ent->next)
    if (ent->plt.refcount > 0)
      break;
  if (ent == NULL
      || fh->elf.root.root.string[0] != '.'
      || fh->elf.root.root.string[1] == '\0')
    return TRUE;

  /* Find the corresponding function descriptor symbol.  Create it
     as undefined if necessary.  */

  fdh = get_fdh (fh, htab);
  if (fdh != NULL)
    while (fdh->elf.root.type == bfd_link_hash_indirect
	   || fdh->elf.root.type == bfd_link_hash_warning)
      fdh = (struct ppc_link_hash_entry *) fdh->elf.root.u.i.link;

  if (fdh == NULL
      && info->shared
      && (fh->elf.root.type == bfd_link_hash_undefined
	  || fh->elf.root.type == bfd_link_hash_undefweak))
    {
      fdh = make_fdh (info, fh);
      if (fdh == NULL)
	return FALSE;
    }

  /* Fake function descriptors are made undefweak.  If the function
     code symbol is strong undefined, make the fake sym the same.
     If the function code symbol is defined, then force the fake
     descriptor local;  We can't support overriding of symbols in a
     shared library on a fake descriptor.  */

  if (fdh != NULL
      && fdh->fake
      && fdh->elf.root.type == bfd_link_hash_undefweak)
    {
      if (fh->elf.root.type == bfd_link_hash_undefined)
	{
	  fdh->elf.root.type = bfd_link_hash_undefined;
	  bfd_link_add_undef (&htab->elf.root, &fdh->elf.root);
	}
      else if (fh->elf.root.type == bfd_link_hash_defined
	       || fh->elf.root.type == bfd_link_hash_defweak)
	{
	  _bfd_elf_link_hash_hide_symbol (info, &fdh->elf, TRUE);
	}
    }

  if (fdh != NULL
      && !fdh->elf.forced_local
      && (info->shared
	  || fdh->elf.def_dynamic
	  || fdh->elf.ref_dynamic
	  || (fdh->elf.root.type == bfd_link_hash_undefweak
	      && ELF_ST_VISIBILITY (fdh->elf.other) == STV_DEFAULT)))
    {
      if (fdh->elf.dynindx == -1)
	if (! bfd_elf_link_record_dynamic_symbol (info, &fdh->elf))
	  return FALSE;
      fdh->elf.ref_regular |= fh->elf.ref_regular;
      fdh->elf.ref_dynamic |= fh->elf.ref_dynamic;
      fdh->elf.ref_regular_nonweak |= fh->elf.ref_regular_nonweak;
      fdh->elf.non_got_ref |= fh->elf.non_got_ref;
      if (ELF_ST_VISIBILITY (fh->elf.other) == STV_DEFAULT)
	{
	  move_plt_plist (fh, fdh);
	  fdh->elf.needs_plt = 1;
	}
      fdh->is_func_descriptor = 1;
      fdh->oh = fh;
      fh->oh = fdh;
    }

  /* Now that the info is on the function descriptor, clear the
     function code sym info.  Any function code syms for which we
     don't have a definition in a regular file, we force local.
     This prevents a shared library from exporting syms that have
     been imported from another library.  Function code syms that
     are really in the library we must leave global to prevent the
     linker dragging in a definition from a static library.  */
  force_local = (!fh->elf.def_regular
		 || fdh == NULL
		 || !fdh->elf.def_regular
		 || fdh->elf.forced_local);
  _bfd_elf_link_hash_hide_symbol (info, &fh->elf, force_local);

  return TRUE;
}