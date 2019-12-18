#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ type; } ;
struct generic_link_hash_entry {TYPE_5__* sym; TYPE_1__ root; } ;
struct bfd_link_info {TYPE_2__* hash; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_14__ {scalar_t__ xvec; } ;
typedef  TYPE_4__ bfd ;
struct TYPE_13__ {struct generic_link_hash_entry* p; } ;
struct TYPE_15__ {int flags; TYPE_3__ udata; int /*<<< orphan*/  value; int /*<<< orphan*/  section; } ;
typedef  TYPE_5__ asymbol ;
struct TYPE_12__ {scalar_t__ creator; } ;

/* Variables and functions */
 int BSF_CONSTRUCTOR ; 
 int BSF_GLOBAL ; 
 int BSF_INDIRECT ; 
 int BSF_OLD_COMMON ; 
 int BSF_WARNING ; 
 int BSF_WEAK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_generic_link_add_one_symbol (struct bfd_link_info*,TYPE_4__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfd_link_hash_entry**) ; 
 char* bfd_asymbol_name (TYPE_5__*) ; 
 int /*<<< orphan*/  bfd_get_section (TYPE_5__*) ; 
 scalar_t__ bfd_is_com_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_is_ind_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_is_und_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_new ; 

__attribute__((used)) static bfd_boolean
generic_link_add_symbol_list (bfd *abfd,
			      struct bfd_link_info *info,
			      bfd_size_type symbol_count,
			      asymbol **symbols,
			      bfd_boolean collect)
{
  asymbol **pp, **ppend;

  pp = symbols;
  ppend = symbols + symbol_count;
  for (; pp < ppend; pp++)
    {
      asymbol *p;

      p = *pp;

      if ((p->flags & (BSF_INDIRECT
		       | BSF_WARNING
		       | BSF_GLOBAL
		       | BSF_CONSTRUCTOR
		       | BSF_WEAK)) != 0
	  || bfd_is_und_section (bfd_get_section (p))
	  || bfd_is_com_section (bfd_get_section (p))
	  || bfd_is_ind_section (bfd_get_section (p)))
	{
	  const char *name;
	  const char *string;
	  struct generic_link_hash_entry *h;
	  struct bfd_link_hash_entry *bh;

	  name = bfd_asymbol_name (p);
	  if (((p->flags & BSF_INDIRECT) != 0
	       || bfd_is_ind_section (p->section))
	      && pp + 1 < ppend)
	    {
	      pp++;
	      string = bfd_asymbol_name (*pp);
	    }
	  else if ((p->flags & BSF_WARNING) != 0
		   && pp + 1 < ppend)
	    {
	      /* The name of P is actually the warning string, and the
		 next symbol is the one to warn about.  */
	      string = name;
	      pp++;
	      name = bfd_asymbol_name (*pp);
	    }
	  else
	    string = NULL;

	  bh = NULL;
	  if (! (_bfd_generic_link_add_one_symbol
		 (info, abfd, name, p->flags, bfd_get_section (p),
		  p->value, string, FALSE, collect, &bh)))
	    return FALSE;
	  h = (struct generic_link_hash_entry *) bh;

	  /* If this is a constructor symbol, and the linker didn't do
             anything with it, then we want to just pass the symbol
             through to the output file.  This will happen when
             linking with -r.  */
	  if ((p->flags & BSF_CONSTRUCTOR) != 0
	      && (h == NULL || h->root.type == bfd_link_hash_new))
	    {
	      p->udata.p = NULL;
	      continue;
	    }

	  /* Save the BFD symbol so that we don't lose any backend
	     specific information that may be attached to it.  We only
	     want this one if it gives more information than the
	     existing one; we don't want to replace a defined symbol
	     with an undefined one.  This routine may be called with a
	     hash table other than the generic hash table, so we only
	     do this if we are certain that the hash table is a
	     generic one.  */
	  if (info->hash->creator == abfd->xvec)
	    {
	      if (h->sym == NULL
		  || (! bfd_is_und_section (bfd_get_section (p))
		      && (! bfd_is_com_section (bfd_get_section (p))
			  || bfd_is_und_section (bfd_get_section (h->sym)))))
		{
		  h->sym = p;
		  /* BSF_OLD_COMMON is a hack to support COFF reloc
		     reading, and it should go away when the COFF
		     linker is switched to the new version.  */
		  if (bfd_is_com_section (bfd_get_section (p)))
		    p->flags |= BSF_OLD_COMMON;
		}
	    }

	  /* Store a back pointer from the symbol to the hash
	     table entry for the benefit of relaxation code until
	     it gets rewritten to not use asymbol structures.
	     Setting this is also used to check whether these
	     symbols were set up by the generic linker.  */
	  p->udata.p = h;
	}
    }

  return TRUE;
}