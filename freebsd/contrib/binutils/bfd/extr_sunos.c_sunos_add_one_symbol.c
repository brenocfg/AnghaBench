#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {TYPE_6__* section; } ;
struct TYPE_26__ {TYPE_3__* p; } ;
struct TYPE_23__ {TYPE_5__* abfd; } ;
struct TYPE_30__ {TYPE_7__ def; TYPE_4__ c; TYPE_1__ undef; } ;
struct TYPE_31__ {scalar_t__ type; TYPE_8__ u; } ;
struct TYPE_19__ {TYPE_9__ root; } ;
struct sunos_link_hash_entry {int flags; int dynindx; TYPE_10__ root; } ;
struct bfd_link_info {TYPE_11__* hash; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_21__ {int flags; scalar_t__ xvec; } ;
typedef  TYPE_12__ bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_28__ {TYPE_5__* owner; } ;
struct TYPE_27__ {int flags; } ;
struct TYPE_25__ {TYPE_2__* section; } ;
struct TYPE_24__ {TYPE_5__* owner; } ;
struct TYPE_22__ {int /*<<< orphan*/  dynsymcount; } ;
struct TYPE_20__ {scalar_t__ creator; } ;

/* Variables and functions */
 int BSF_CONSTRUCTOR ; 
 int BSF_INDIRECT ; 
 int BSF_WARNING ; 
 int DYNAMIC ; 
 int /*<<< orphan*/  FALSE ; 
 int SUNOS_CONSTRUCTOR ; 
 int SUNOS_DEF_DYNAMIC ; 
 int SUNOS_DEF_REGULAR ; 
 int SUNOS_REF_DYNAMIC ; 
 int SUNOS_REF_REGULAR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_generic_link_add_one_symbol (struct bfd_link_info*,TYPE_12__*,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfd_link_hash_entry**) ; 
 scalar_t__ bfd_is_com_section (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_is_und_section (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_link_hash_common ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_new ; 
 scalar_t__ bfd_link_hash_undefined ; 
 int /*<<< orphan*/ * bfd_und_section_ptr ; 
 scalar_t__ bfd_wrapped_link_hash_lookup (TYPE_12__*,struct bfd_link_info*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obj_bsssec (TYPE_12__*) ; 
 TYPE_13__* sunos_hash_table (struct bfd_link_info*) ; 
 struct sunos_link_hash_entry* sunos_link_hash_lookup (TYPE_13__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
sunos_add_one_symbol (struct bfd_link_info *info,
		      bfd *abfd,
		      const char *name,
		      flagword flags,
		      asection *section,
		      bfd_vma value,
		      const char *string,
		      bfd_boolean copy,
		      bfd_boolean collect,
		      struct bfd_link_hash_entry **hashp)
{
  struct sunos_link_hash_entry *h;
  int new_flag;

  if ((flags & (BSF_INDIRECT | BSF_WARNING | BSF_CONSTRUCTOR)) != 0
      || ! bfd_is_und_section (section))
    h = sunos_link_hash_lookup (sunos_hash_table (info), name, TRUE, copy,
				FALSE);
  else
    h = ((struct sunos_link_hash_entry *)
	 bfd_wrapped_link_hash_lookup (abfd, info, name, TRUE, copy, FALSE));
  if (h == NULL)
    return FALSE;

  if (hashp != NULL)
    *hashp = (struct bfd_link_hash_entry *) h;

  /* Treat a common symbol in a dynamic object as defined in the .bss
     section of the dynamic object.  We don't want to allocate space
     for it in our process image.  */
  if ((abfd->flags & DYNAMIC) != 0
      && bfd_is_com_section (section))
    section = obj_bsssec (abfd);

  if (! bfd_is_und_section (section)
      && h->root.root.type != bfd_link_hash_new
      && h->root.root.type != bfd_link_hash_undefined
      && h->root.root.type != bfd_link_hash_defweak)
    {
      /* We are defining the symbol, and it is already defined.  This
	 is a potential multiple definition error.  */
      if ((abfd->flags & DYNAMIC) != 0)
	{
	  /* The definition we are adding is from a dynamic object.
	     We do not want this new definition to override the
	     existing definition, so we pretend it is just a
	     reference.  */
	  section = bfd_und_section_ptr;
	}
      else if (h->root.root.type == bfd_link_hash_defined
	       && h->root.root.u.def.section->owner != NULL
	       && (h->root.root.u.def.section->owner->flags & DYNAMIC) != 0)
	{
	  /* The existing definition is from a dynamic object.  We
	     want to override it with the definition we just found.
	     Clobber the existing definition.  */
	  h->root.root.type = bfd_link_hash_undefined;
	  h->root.root.u.undef.abfd = h->root.root.u.def.section->owner;
	}
      else if (h->root.root.type == bfd_link_hash_common
	       && (h->root.root.u.c.p->section->owner->flags & DYNAMIC) != 0)
	{
	  /* The existing definition is from a dynamic object.  We
	     want to override it with the definition we just found.
	     Clobber the existing definition.  We can't set it to new,
	     because it is on the undefined list.  */
	  h->root.root.type = bfd_link_hash_undefined;
	  h->root.root.u.undef.abfd = h->root.root.u.c.p->section->owner;
	}
    }

  if ((abfd->flags & DYNAMIC) != 0
      && abfd->xvec == info->hash->creator
      && (h->flags & SUNOS_CONSTRUCTOR) != 0)
    /* The existing symbol is a constructor symbol, and this symbol
       is from a dynamic object.  A constructor symbol is actually a
       definition, although the type will be bfd_link_hash_undefined
       at this point.  We want to ignore the definition from the
       dynamic object.  */
    section = bfd_und_section_ptr;
  else if ((flags & BSF_CONSTRUCTOR) != 0
	   && (abfd->flags & DYNAMIC) == 0
	   && h->root.root.type == bfd_link_hash_defined
	   && h->root.root.u.def.section->owner != NULL
	   && (h->root.root.u.def.section->owner->flags & DYNAMIC) != 0)
    /* The existing symbol is defined by a dynamic object, and this
       is a constructor symbol.  As above, we want to force the use
       of the constructor symbol from the regular object.  */
    h->root.root.type = bfd_link_hash_new;

  /* Do the usual procedure for adding a symbol.  */
  if (! _bfd_generic_link_add_one_symbol (info, abfd, name, flags, section,
					  value, string, copy, collect,
					  hashp))
    return FALSE;

  if (abfd->xvec == info->hash->creator)
    {
      /* Set a flag in the hash table entry indicating the type of
	 reference or definition we just found.  Keep a count of the
	 number of dynamic symbols we find.  A dynamic symbol is one
	 which is referenced or defined by both a regular object and a
	 shared object.  */
      if ((abfd->flags & DYNAMIC) == 0)
	{
	  if (bfd_is_und_section (section))
	    new_flag = SUNOS_REF_REGULAR;
	  else
	    new_flag = SUNOS_DEF_REGULAR;
	}
      else
	{
	  if (bfd_is_und_section (section))
	    new_flag = SUNOS_REF_DYNAMIC;
	  else
	    new_flag = SUNOS_DEF_DYNAMIC;
	}
      h->flags |= new_flag;

      if (h->dynindx == -1
	  && (h->flags & (SUNOS_DEF_REGULAR | SUNOS_REF_REGULAR)) != 0)
	{
	  ++sunos_hash_table (info)->dynsymcount;
	  h->dynindx = -2;
	}

      if ((flags & BSF_CONSTRUCTOR) != 0
	  && (abfd->flags & DYNAMIC) == 0)
	h->flags |= SUNOS_CONSTRUCTOR;
    }

  return TRUE;
}