#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_21__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_16__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct xcoff_loader_info {int /*<<< orphan*/  output_bfd; scalar_t__ ldsym_count; void* failed; TYPE_15__* info; scalar_t__ export_defineds; } ;
struct TYPE_23__ {char* string; } ;
struct TYPE_38__ {scalar_t__ size; TYPE_7__* p; } ;
struct TYPE_36__ {int /*<<< orphan*/  value; TYPE_13__* section; } ;
struct TYPE_30__ {scalar_t__ link; } ;
struct TYPE_39__ {TYPE_8__ c; TYPE_6__ def; TYPE_1__ i; } ;
struct TYPE_24__ {scalar_t__ type; TYPE_10__ root; TYPE_9__ u; } ;
struct TYPE_34__ {int toc_offset; } ;
struct xcoff_link_hash_entry {int flags; int indx; TYPE_11__ root; TYPE_16__* ldsym; scalar_t__ ldindx; int /*<<< orphan*/  smclas; struct xcoff_link_hash_entry* descriptor; TYPE_5__* toc_section; TYPE_4__ u; } ;
struct internal_ldsym {int dummy; } ;
typedef  int bfd_size_type ;
typedef  void* bfd_boolean ;
struct TYPE_25__ {int flags; } ;
typedef  TYPE_12__ bfd ;
struct TYPE_26__ {int reloc_count; int /*<<< orphan*/  size; TYPE_2__* owner; } ;
typedef  TYPE_13__ asection ;
struct TYPE_37__ {TYPE_21__* section; } ;
struct TYPE_35__ {int size; int /*<<< orphan*/  reloc_count; } ;
struct TYPE_33__ {scalar_t__ creator; } ;
struct TYPE_32__ {int flags; scalar_t__ xvec; TYPE_12__* my_archive; } ;
struct TYPE_31__ {scalar_t__ size; } ;
struct TYPE_29__ {scalar_t__ l_ifile; } ;
struct TYPE_28__ {TYPE_3__* hash; } ;
struct TYPE_27__ {scalar_t__ gc; scalar_t__ ldrel_count; TYPE_13__* descriptor_section; TYPE_5__* toc_section; TYPE_13__* linkage_section; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int DYNAMIC ; 
 void* FALSE ; 
 void* TRUE ; 
 int XCOFF_BUILT_LDSYM ; 
 int XCOFF_CALLED ; 
 int XCOFF_DEF_DYNAMIC ; 
 int XCOFF_DEF_REGULAR ; 
 int XCOFF_DESCRIPTOR ; 
 int XCOFF_ENTRY ; 
 int XCOFF_EXPORT ; 
 int XCOFF_IMPORT ; 
 int XCOFF_LDREL ; 
 int XCOFF_MARK ; 
 int XCOFF_REF_REGULAR ; 
 int XCOFF_RTINIT ; 
 int XCOFF_SET_TOC ; 
 int /*<<< orphan*/  XMC_DS ; 
 int /*<<< orphan*/  XMC_GL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bfd_is_abs_section (TYPE_13__*) ; 
 int bfd_is_com_section (TYPE_21__*) ; 
 scalar_t__ bfd_link_hash_common ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_undefined ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_12__* bfd_openr_next_archived_file (TYPE_12__*,TYPE_12__*) ; 
 scalar_t__ bfd_xcoff_function_descriptor_size (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_xcoff_glink_code_size (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_xcoff_is_xcoff32 (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_xcoff_is_xcoff64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_xcoff_put_ldsymbol_name (int /*<<< orphan*/ ,struct xcoff_loader_info*,TYPE_16__*,char*) ; 
 TYPE_16__* bfd_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 TYPE_14__* xcoff_hash_table (TYPE_15__*) ; 

__attribute__((used)) static bfd_boolean
xcoff_build_ldsyms (struct xcoff_link_hash_entry *h, void * p)
{
  struct xcoff_loader_info *ldinfo = (struct xcoff_loader_info *) p;
  bfd_size_type amt;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct xcoff_link_hash_entry *) h->root.u.i.link;

  /* __rtinit, this symbol has special handling. */
  if (h->flags & XCOFF_RTINIT)
      return TRUE;

  /* If this is a final link, and the symbol was defined as a common
     symbol in a regular object file, and there was no definition in
     any dynamic object, then the linker will have allocated space for
     the symbol in a common section but the XCOFF_DEF_REGULAR flag
     will not have been set.  */
  if (h->root.type == bfd_link_hash_defined
      && (h->flags & XCOFF_DEF_REGULAR) == 0
      && (h->flags & XCOFF_REF_REGULAR) != 0
      && (h->flags & XCOFF_DEF_DYNAMIC) == 0
      && (bfd_is_abs_section (h->root.u.def.section)
	  || (h->root.u.def.section->owner->flags & DYNAMIC) == 0))
    h->flags |= XCOFF_DEF_REGULAR;

  /* If all defined symbols should be exported, mark them now.  We
     don't want to export the actual functions, just the function
     descriptors.  */
  if (ldinfo->export_defineds
      && (h->flags & XCOFF_DEF_REGULAR) != 0
      && h->root.root.string[0] != '.')
    {
      bfd_boolean export;

      /* We don't export a symbol which is being defined by an object
	 included from an archive which contains a shared object.  The
	 rationale is that if an archive contains both an unshared and
	 a shared object, then there must be some reason that the
	 unshared object is unshared, and we don't want to start
	 providing a shared version of it.  In particular, this solves
	 a bug involving the _savefNN set of functions.  gcc will call
	 those functions without providing a slot to restore the TOC,
	 so it is essential that these functions be linked in directly
	 and not from a shared object, which means that a shared
	 object which also happens to link them in must not export
	 them.  This is confusing, but I haven't been able to think of
	 a different approach.  Note that the symbols can, of course,
	 be exported explicitly.  */
      export = TRUE;
      if ((h->root.type == bfd_link_hash_defined
	   || h->root.type == bfd_link_hash_defweak)
	  && h->root.u.def.section->owner != NULL
	  && h->root.u.def.section->owner->my_archive != NULL)
	{
	  bfd *arbfd, *member;

	  arbfd = h->root.u.def.section->owner->my_archive;
	  member = bfd_openr_next_archived_file (arbfd, NULL);
	  while (member != NULL)
	    {
	      if ((member->flags & DYNAMIC) != 0)
		{
		  export = FALSE;
		  break;
		}
	      member = bfd_openr_next_archived_file (arbfd, member);
	    }
	}

      if (export)
	h->flags |= XCOFF_EXPORT;
    }

  /* We don't want to garbage collect symbols which are not defined in
     XCOFF files.  This is a convenient place to mark them.  */
  if (xcoff_hash_table (ldinfo->info)->gc
      && (h->flags & XCOFF_MARK) == 0
      && (h->root.type == bfd_link_hash_defined
	  || h->root.type == bfd_link_hash_defweak)
      && (h->root.u.def.section->owner == NULL
	  || (h->root.u.def.section->owner->xvec
	      != ldinfo->info->hash->creator)))
    h->flags |= XCOFF_MARK;

  /* If this symbol is called and defined in a dynamic object, or it
     is imported, then we need to set up global linkage code for it.
     (Unless we did garbage collection and we didn't need this
     symbol.)  */
  if ((h->flags & XCOFF_CALLED) != 0
      && (h->root.type == bfd_link_hash_undefined
	  || h->root.type == bfd_link_hash_undefweak)
      && h->root.root.string[0] == '.'
      && h->descriptor != NULL
      && ((h->descriptor->flags & XCOFF_DEF_DYNAMIC) != 0
	  || ((h->descriptor->flags & XCOFF_IMPORT) != 0
	      && (h->descriptor->flags & XCOFF_DEF_REGULAR) == 0))
      && (! xcoff_hash_table (ldinfo->info)->gc
	  || (h->flags & XCOFF_MARK) != 0))
    {
      asection *sec;
      struct xcoff_link_hash_entry *hds;

      sec = xcoff_hash_table (ldinfo->info)->linkage_section;
      h->root.type = bfd_link_hash_defined;
      h->root.u.def.section = sec;
      h->root.u.def.value = sec->size;
      h->smclas = XMC_GL;
      h->flags |= XCOFF_DEF_REGULAR;
      sec->size += bfd_xcoff_glink_code_size(ldinfo->output_bfd);

      /* The global linkage code requires a TOC entry for the
	 descriptor.  */
      hds = h->descriptor;
      BFD_ASSERT ((hds->root.type == bfd_link_hash_undefined
		   || hds->root.type == bfd_link_hash_undefweak)
		  && (hds->flags & XCOFF_DEF_REGULAR) == 0);
      hds->flags |= XCOFF_MARK;
      if (hds->toc_section == NULL)
	{
	  int byte_size;

	  /* 32 vs 64
	     xcoff32 uses 4 bytes in the toc.
	     xcoff64 uses 8 bytes in the toc.  */
	  if (bfd_xcoff_is_xcoff64 (ldinfo->output_bfd))
	    byte_size = 8;
	  else if (bfd_xcoff_is_xcoff32 (ldinfo->output_bfd))
	    byte_size = 4;
	  else
	    return FALSE;

	  hds->toc_section = xcoff_hash_table (ldinfo->info)->toc_section;
	  hds->u.toc_offset = hds->toc_section->size;
	  hds->toc_section->size += byte_size;
	  ++xcoff_hash_table (ldinfo->info)->ldrel_count;
	  ++hds->toc_section->reloc_count;
	  hds->indx = -2;
	  hds->flags |= XCOFF_SET_TOC | XCOFF_LDREL;

	  /* We need to call xcoff_build_ldsyms recursively here,
	     because we may already have passed hds on the traversal.  */
	  xcoff_build_ldsyms (hds, p);
	}
    }

  /* If this symbol is exported, but not defined, we need to try to
     define it.  */
  if ((h->flags & XCOFF_EXPORT) != 0
      && (h->flags & XCOFF_IMPORT) == 0
      && (h->flags & XCOFF_DEF_REGULAR) == 0
      && (h->flags & XCOFF_DEF_DYNAMIC) == 0
      && (h->root.type == bfd_link_hash_undefined
	  || h->root.type == bfd_link_hash_undefweak))
    {
      if ((h->flags & XCOFF_DESCRIPTOR) != 0
	  && (h->descriptor->root.type == bfd_link_hash_defined
	      || h->descriptor->root.type == bfd_link_hash_defweak))
	{
	  asection *sec;

	  /* This is an undefined function descriptor associated with
	     a defined entry point.  We can build up a function
	     descriptor ourselves.  Believe it or not, the AIX linker
	     actually does this, and there are cases where we need to
	     do it as well.  */
	  sec = xcoff_hash_table (ldinfo->info)->descriptor_section;
	  h->root.type = bfd_link_hash_defined;
	  h->root.u.def.section = sec;
	  h->root.u.def.value = sec->size;
	  h->smclas = XMC_DS;
	  h->flags |= XCOFF_DEF_REGULAR;

	  /* The size of the function descriptor depends if this is an
	     xcoff32 (12) or xcoff64 (24).  */
	  sec->size +=
	    bfd_xcoff_function_descriptor_size(ldinfo->output_bfd);

	  /* A function descriptor uses two relocs: one for the
	     associated code, and one for the TOC address.  */
	  xcoff_hash_table (ldinfo->info)->ldrel_count += 2;
	  sec->reloc_count += 2;

	  /* We handle writing out the contents of the descriptor in
	     xcoff_write_global_symbol.  */
	}
      else
	{
	  (*_bfd_error_handler)
	    (_("warning: attempt to export undefined symbol `%s'"),
	     h->root.root.string);
	  h->ldsym = NULL;
	  return TRUE;
	}
    }

  /* If this is still a common symbol, and it wasn't garbage
     collected, we need to actually allocate space for it in the .bss
     section.  */
  if (h->root.type == bfd_link_hash_common
      && (! xcoff_hash_table (ldinfo->info)->gc
	  || (h->flags & XCOFF_MARK) != 0)
      && h->root.u.c.p->section->size == 0)
    {
      BFD_ASSERT (bfd_is_com_section (h->root.u.c.p->section));
      h->root.u.c.p->section->size = h->root.u.c.size;
    }

  /* We need to add a symbol to the .loader section if it is mentioned
     in a reloc which we are copying to the .loader section and it was
     not defined or common, or if it is the entry point, or if it is
     being exported.  */

  if (((h->flags & XCOFF_LDREL) == 0
       || h->root.type == bfd_link_hash_defined
       || h->root.type == bfd_link_hash_defweak
       || h->root.type == bfd_link_hash_common)
      && (h->flags & XCOFF_ENTRY) == 0
      && (h->flags & XCOFF_EXPORT) == 0)
    {
      h->ldsym = NULL;
      return TRUE;
    }

  /* We don't need to add this symbol if we did garbage collection and
     we did not mark this symbol.  */
  if (xcoff_hash_table (ldinfo->info)->gc
      && (h->flags & XCOFF_MARK) == 0)
    {
      h->ldsym = NULL;
      return TRUE;
    }

  /* We may have already processed this symbol due to the recursive
     call above.  */
  if ((h->flags & XCOFF_BUILT_LDSYM) != 0)
    return TRUE;

  /* We need to add this symbol to the .loader symbols.  */

  BFD_ASSERT (h->ldsym == NULL);
  amt = sizeof (struct internal_ldsym);
  h->ldsym = bfd_zalloc (ldinfo->output_bfd, amt);
  if (h->ldsym == NULL)
    {
      ldinfo->failed = TRUE;
      return FALSE;
    }

  if ((h->flags & XCOFF_IMPORT) != 0)
    h->ldsym->l_ifile = h->ldindx;

  /* The first 3 symbol table indices are reserved to indicate the
     data, text and bss sections.  */
  h->ldindx = ldinfo->ldsym_count + 3;

  ++ldinfo->ldsym_count;

  if (! bfd_xcoff_put_ldsymbol_name (ldinfo->output_bfd, ldinfo,
				     h->ldsym, h->root.root.string))
    return FALSE;

  h->flags |= XCOFF_BUILT_LDSYM;

  return TRUE;
}