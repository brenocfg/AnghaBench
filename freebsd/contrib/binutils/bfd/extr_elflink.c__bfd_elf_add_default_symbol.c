#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct bfd_link_hash_entry* link; } ;
struct TYPE_12__ {TYPE_1__ i; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {int ref_dynamic; scalar_t__ ref_regular; struct bfd_link_hash_entry root; scalar_t__ def_regular; scalar_t__ def_dynamic; } ;
struct elf_backend_data {int collect; int /*<<< orphan*/  (* elf_backend_copy_indirect_symbol ) (struct bfd_link_info*,struct elf_link_hash_entry*,struct elf_link_hash_entry*) ;} ;
struct bfd_link_info {scalar_t__ shared; TYPE_3__* hash; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int bfd_boolean ;
struct TYPE_14__ {int flags; } ;
typedef  TYPE_4__ bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_13__ {int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSF_INDIRECT ; 
 int DYNAMIC ; 
 char ELF_VER_CHR ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_elf_merge_symbol (TYPE_4__*,struct bfd_link_info*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct elf_link_hash_entry**,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  _bfd_generic_link_add_one_symbol (struct bfd_link_info*,TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int,struct bfd_link_hash_entry**) ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 char* bfd_hash_allocate (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  bfd_ind_section_ptr ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 int /*<<< orphan*/  elf_hash_table (struct bfd_link_info*) ; 
 struct elf_link_hash_entry* elf_link_hash_lookup (int /*<<< orphan*/ ,char const*,int,int,int) ; 
 struct elf_backend_data* get_elf_backend_data (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct bfd_link_info*,struct elf_link_hash_entry*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub3 (struct bfd_link_info*,struct elf_link_hash_entry*,struct elf_link_hash_entry*) ; 

bfd_boolean
_bfd_elf_add_default_symbol (bfd *abfd,
			     struct bfd_link_info *info,
			     struct elf_link_hash_entry *h,
			     const char *name,
			     Elf_Internal_Sym *sym,
			     asection **psec,
			     bfd_vma *value,
			     bfd_boolean *dynsym,
			     bfd_boolean override)
{
  bfd_boolean type_change_ok;
  bfd_boolean size_change_ok;
  bfd_boolean skip;
  char *shortname;
  struct elf_link_hash_entry *hi;
  struct bfd_link_hash_entry *bh;
  const struct elf_backend_data *bed;
  bfd_boolean collect;
  bfd_boolean dynamic;
  char *p;
  size_t len, shortlen;
  asection *sec;

  /* If this symbol has a version, and it is the default version, we
     create an indirect symbol from the default name to the fully
     decorated name.  This will cause external references which do not
     specify a version to be bound to this version of the symbol.  */
  p = strchr (name, ELF_VER_CHR);
  if (p == NULL || p[1] != ELF_VER_CHR)
    return TRUE;

  if (override)
    {
      /* We are overridden by an old definition. We need to check if we
	 need to create the indirect symbol from the default name.  */
      hi = elf_link_hash_lookup (elf_hash_table (info), name, TRUE,
				 FALSE, FALSE);
      BFD_ASSERT (hi != NULL);
      if (hi == h)
	return TRUE;
      while (hi->root.type == bfd_link_hash_indirect
	     || hi->root.type == bfd_link_hash_warning)
	{
	  hi = (struct elf_link_hash_entry *) hi->root.u.i.link;
	  if (hi == h)
	    return TRUE;
	}
    }

  bed = get_elf_backend_data (abfd);
  collect = bed->collect;
  dynamic = (abfd->flags & DYNAMIC) != 0;

  shortlen = p - name;
  shortname = bfd_hash_allocate (&info->hash->table, shortlen + 1);
  if (shortname == NULL)
    return FALSE;
  memcpy (shortname, name, shortlen);
  shortname[shortlen] = '\0';

  /* We are going to create a new symbol.  Merge it with any existing
     symbol with this name.  For the purposes of the merge, act as
     though we were defining the symbol we just defined, although we
     actually going to define an indirect symbol.  */
  type_change_ok = FALSE;
  size_change_ok = FALSE;
  sec = *psec;
  if (!_bfd_elf_merge_symbol (abfd, info, shortname, sym, &sec, value,
			      NULL, &hi, &skip, &override,
			      &type_change_ok, &size_change_ok))
    return FALSE;

  if (skip)
    goto nondefault;

  if (! override)
    {
      bh = &hi->root;
      if (! (_bfd_generic_link_add_one_symbol
	     (info, abfd, shortname, BSF_INDIRECT, bfd_ind_section_ptr,
	      0, name, FALSE, collect, &bh)))
	return FALSE;
      hi = (struct elf_link_hash_entry *) bh;
    }
  else
    {
      /* In this case the symbol named SHORTNAME is overriding the
	 indirect symbol we want to add.  We were planning on making
	 SHORTNAME an indirect symbol referring to NAME.  SHORTNAME
	 is the name without a version.  NAME is the fully versioned
	 name, and it is the default version.

	 Overriding means that we already saw a definition for the
	 symbol SHORTNAME in a regular object, and it is overriding
	 the symbol defined in the dynamic object.

	 When this happens, we actually want to change NAME, the
	 symbol we just added, to refer to SHORTNAME.  This will cause
	 references to NAME in the shared object to become references
	 to SHORTNAME in the regular object.  This is what we expect
	 when we override a function in a shared object: that the
	 references in the shared object will be mapped to the
	 definition in the regular object.  */

      while (hi->root.type == bfd_link_hash_indirect
	     || hi->root.type == bfd_link_hash_warning)
	hi = (struct elf_link_hash_entry *) hi->root.u.i.link;

      h->root.type = bfd_link_hash_indirect;
      h->root.u.i.link = (struct bfd_link_hash_entry *) hi;
      if (h->def_dynamic)
	{
	  h->def_dynamic = 0;
	  hi->ref_dynamic = 1;
	  if (hi->ref_regular
	      || hi->def_regular)
	    {
	      if (! bfd_elf_link_record_dynamic_symbol (info, hi))
		return FALSE;
	    }
	}

      /* Now set HI to H, so that the following code will set the
	 other fields correctly.  */
      hi = h;
    }

  /* Check if HI is a warning symbol.  */
  if (hi->root.type == bfd_link_hash_warning)
    hi = (struct elf_link_hash_entry *) hi->root.u.i.link;

  /* If there is a duplicate definition somewhere, then HI may not
     point to an indirect symbol.  We will have reported an error to
     the user in that case.  */

  if (hi->root.type == bfd_link_hash_indirect)
    {
      struct elf_link_hash_entry *ht;

      ht = (struct elf_link_hash_entry *) hi->root.u.i.link;
      (*bed->elf_backend_copy_indirect_symbol) (info, ht, hi);

      /* See if the new flags lead us to realize that the symbol must
	 be dynamic.  */
      if (! *dynsym)
	{
	  if (! dynamic)
	    {
	      if (info->shared
		  || hi->ref_dynamic)
		*dynsym = TRUE;
	    }
	  else
	    {
	      if (hi->ref_regular)
		*dynsym = TRUE;
	    }
	}
    }

  /* We also need to define an indirection from the nondefault version
     of the symbol.  */

nondefault:
  len = strlen (name);
  shortname = bfd_hash_allocate (&info->hash->table, len);
  if (shortname == NULL)
    return FALSE;
  memcpy (shortname, name, shortlen);
  memcpy (shortname + shortlen, p + 1, len - shortlen);

  /* Once again, merge with any existing symbol.  */
  type_change_ok = FALSE;
  size_change_ok = FALSE;
  sec = *psec;
  if (!_bfd_elf_merge_symbol (abfd, info, shortname, sym, &sec, value,
			      NULL, &hi, &skip, &override,
			      &type_change_ok, &size_change_ok))
    return FALSE;

  if (skip)
    return TRUE;

  if (override)
    {
      /* Here SHORTNAME is a versioned name, so we don't expect to see
	 the type of override we do in the case above unless it is
	 overridden by a versioned definition.  */
      if (hi->root.type != bfd_link_hash_defined
	  && hi->root.type != bfd_link_hash_defweak)
	(*_bfd_error_handler)
	  (_("%B: unexpected redefinition of indirect versioned symbol `%s'"),
	   abfd, shortname);
    }
  else
    {
      bh = &hi->root;
      if (! (_bfd_generic_link_add_one_symbol
	     (info, abfd, shortname, BSF_INDIRECT,
	      bfd_ind_section_ptr, 0, name, FALSE, collect, &bh)))
	return FALSE;
      hi = (struct elf_link_hash_entry *) bh;

      /* If there is a duplicate definition somewhere, then HI may not
	 point to an indirect symbol.  We will have reported an error
	 to the user in that case.  */

      if (hi->root.type == bfd_link_hash_indirect)
	{
	  (*bed->elf_backend_copy_indirect_symbol) (info, h, hi);

	  /* See if the new flags lead us to realize that the symbol
	     must be dynamic.  */
	  if (! *dynsym)
	    {
	      if (! dynamic)
		{
		  if (info->shared
		      || hi->ref_dynamic)
		    *dynsym = TRUE;
		}
	      else
		{
		  if (hi->ref_regular)
		    *dynsym = TRUE;
		}
	    }
	}
    }

  return TRUE;
}