#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_16__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  global; } ;
struct TYPE_18__ {unsigned long location; int /*<<< orphan*/  global; } ;
struct TYPE_17__ {int kind; scalar_t__ extension; } ;
struct TYPE_28__ {int index; } ;
struct TYPE_29__ {TYPE_7__ dnttp; } ;
struct TYPE_30__ {TYPE_8__ type; } ;
struct TYPE_27__ {int global; } ;
struct TYPE_26__ {int /*<<< orphan*/  regvar; } ;
struct TYPE_25__ {int const endkind; } ;
struct TYPE_24__ {unsigned long hiaddr; unsigned long lowaddr; int /*<<< orphan*/  global; } ;
struct TYPE_23__ {unsigned long hiaddr; unsigned long lowaddr; int /*<<< orphan*/  global; } ;
union dnttentry {TYPE_12__ dconst; TYPE_11__ dsvar; TYPE_10__ dblock; TYPE_9__ dtype; TYPE_6__ dtag; TYPE_5__ ddvar; TYPE_4__ dend; TYPE_3__ ddocfunc; TYPE_2__ dfunc; } ;
struct partial_symtab {char* filename; TYPE_1__* objfile; } ;
struct TYPE_21__ {int /*<<< orphan*/  next; } ;
struct objfile {char* name; TYPE_16__ static_psymbols; TYPE_16__ global_psymbols; int /*<<< orphan*/  section_offsets; } ;
struct dntt_type_block {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  enum address_class { ____Placeholder_address_class } address_class ;
typedef  int /*<<< orphan*/  domain_enum ;
struct TYPE_22__ {int /*<<< orphan*/  objfile_obstack; } ;
struct TYPE_20__ {int globals; } ;
typedef  TYPE_13__ PXDB_header ;

/* Variables and functions */
 unsigned long ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  DNTT_TYPE_BEGIN 140 
 int const DNTT_TYPE_CLASS ; 
#define  DNTT_TYPE_CONST 139 
#define  DNTT_TYPE_DOC_FUNCTION 138 
#define  DNTT_TYPE_DVAR 137 
#define  DNTT_TYPE_END 136 
#define  DNTT_TYPE_ENTRY 135 
 int const DNTT_TYPE_ENUM ; 
#define  DNTT_TYPE_FUNCTION 134 
#define  DNTT_TYPE_MEMENUM 133 
#define  DNTT_TYPE_MODULE 132 
#define  DNTT_TYPE_SRCFILE 131 
#define  DNTT_TYPE_SVAR 130 
#define  DNTT_TYPE_TAGDEF 129 
 int const DNTT_TYPE_TEMPLATE ; 
#define  DNTT_TYPE_TYPEDEF 128 
 int /*<<< orphan*/  GNTT (struct objfile*) ; 
 int GNTT_SYMCOUNT (struct objfile*) ; 
 int LNTT_SYMCOUNT (struct objfile*) ; 
 int LOC_BLOCK ; 
 int LOC_CONST ; 
 int LOC_LOCAL ; 
 int LOC_REGISTER ; 
 int LOC_STATIC ; 
 int LOC_UNDEF ; 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  SECT_OFF_DATA (struct objfile*) ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  VT (struct objfile*) ; 
 int /*<<< orphan*/  add_psymbol_to_list (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_16__*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct objfile*) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  free_pending_blocks () ; 
 int /*<<< orphan*/  hpread_end_psymtab (struct partial_symtab*,char**,int,int,int,struct partial_symtab**,int) ; 
 union dnttentry* hpread_get_gntt (int,struct objfile*) ; 
 scalar_t__ hpread_get_header (struct objfile*,TYPE_13__*) ; 
 union dnttentry* hpread_get_lntt (int,struct objfile*) ; 
 unsigned long hpread_get_textlow (int,int,struct objfile*,int) ; 
 int hpread_quick_traverse (struct objfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_13__*) ; 
 struct partial_symtab* hpread_start_psymtab (struct objfile*,char*,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  language_unknown ; 
 scalar_t__ last_source_file ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup_free_objfile (struct objfile*) ; 
 int /*<<< orphan*/  memcpy (char**,char**,int) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  really_free_pendings ; 
 int /*<<< orphan*/  set_namestring (union dnttentry*,char**,struct objfile*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strrchr (char*,char) ; 

void
hpread_build_psymtabs (struct objfile *objfile, int mainline)
{

#ifdef DUMPING
  /* Turn this on to get debugging output. */
  static int dumping = 0;
#endif

  char *namestring;
  int past_first_source_file = 0;
  struct cleanup *old_chain;

  int hp_symnum, symcount, i;
  int scan_start = 0;

  union dnttentry *dn_bufp;
  unsigned long valu;
  char *p;
  int texthigh = 0;
  int have_name = 0;

  /* Current partial symtab */
  struct partial_symtab *pst;

  /* List of current psymtab's include files */
  char **psymtab_include_list;
  int includes_allocated;
  int includes_used;

  /* Index within current psymtab dependency list */
  struct partial_symtab **dependency_list;
  int dependencies_used, dependencies_allocated;

  /* Just in case the stabs reader left turds lying around.  */
  free_pending_blocks ();
  make_cleanup (really_free_pendings, 0);

  pst = (struct partial_symtab *) 0;

  /* We shouldn't use alloca, instead use malloc/free.  Doing so avoids
     a number of problems with cross compilation and creating useless holes
     in the stack when we have to allocate new entries.  FIXME.  */

  includes_allocated = 30;
  includes_used = 0;
  psymtab_include_list = (char **) alloca (includes_allocated *
					   sizeof (char *));

  dependencies_allocated = 30;
  dependencies_used = 0;
  dependency_list =
    (struct partial_symtab **) alloca (dependencies_allocated *
				       sizeof (struct partial_symtab *));

  old_chain = make_cleanup_free_objfile (objfile);

  last_source_file = 0;

#ifdef QUICK_LOOK_UP
  {
    /* Begin code for new-style loading of quick look-up tables. */

    /* elz: this checks whether the file has beeen processed by pxdb.
       If not we would like to try to read the psymbols in
       anyway, but it turns out to be not so easy. So this could 
       actually be commented out, but I leave it in, just in case
       we decide to add support for non-pxdb-ed stuff in the future. */
    PXDB_header pxdb_header;
    int found_modules_in_program;

    if (hpread_get_header (objfile, &pxdb_header))
      {
	/* Build a minimal table.  No types, no global variables,
	   no include files.... */
#ifdef DUMPING
	if (dumping)
	  printf ("\nNew method for %s\n", objfile->name);
#endif

	/* elz: quick_traverse returns true if it found
	   some modules in the main source file, other
	   than those in end.c
	   In C and C++, all the files have MODULES entries
	   in the LNTT, and the quick table traverse is all 
	   based on finding these MODULES entries. Without 
	   those it cannot work. 
	   It happens that F77 programs don't have MODULES
	   so the quick traverse gets confused. F90 programs
	   have modules, and the quick method still works.
	   So, if modules (other than those in end.c) are
	   not found we give up on the quick table stuff, 
	   and fall back on the slower method  */
	found_modules_in_program = hpread_quick_traverse (objfile,
							  GNTT (objfile),
							  VT (objfile),
							  &pxdb_header);

	discard_cleanups (old_chain);

	/* Set up to scan the global section of the LNTT.

	   This field is not always correct: if there are
	   no globals, it will point to the last record in
	   the regular LNTT, which is usually an END MODULE.

	   Since it might happen that there could be a file
	   with just one global record, there's no way to
	   tell other than by looking at the record, so that's
	   done below. */
	if (found_modules_in_program)
	  scan_start = pxdb_header.globals;
      }
#ifdef DUMPING
    else
      {
	if (dumping)
	  printf ("\nGoing on to old method for %s\n", objfile->name);
      }
#endif
  }
#endif /* QUICK_LOOK_UP */

  /* Make two passes, one over the GNTT symbols, the other for the
     LNTT symbols.

     JB comment: above isn't true--they only make one pass, over
     the LNTT.  */
  for (i = 0; i < 1; i++)
    {
      int within_function = 0;

      if (i)
	symcount = GNTT_SYMCOUNT (objfile);
      else
	symcount = LNTT_SYMCOUNT (objfile);


      for (hp_symnum = scan_start; hp_symnum < symcount; hp_symnum++)
	{
	  QUIT;
	  if (i)
	    dn_bufp = hpread_get_gntt (hp_symnum, objfile);
	  else
	    dn_bufp = hpread_get_lntt (hp_symnum, objfile);

	  if (dn_bufp->dblock.extension)
	    continue;

	  /* Only handle things which are necessary for minimal symbols.
	     everything else is ignored.  */
	  switch (dn_bufp->dblock.kind)
	    {
	    case DNTT_TYPE_SRCFILE:
	      {
#ifdef QUICK_LOOK_UP
		if (scan_start == hp_symnum
		    && symcount == hp_symnum + 1)
		  {
		    /* If there are NO globals in an executable,
		       PXDB's index to the globals will point to
		       the last record in the file, which 
		       could be this record. (this happened for F77 libraries)
		       ignore it and be done! */
		    continue;
		  }
#endif /* QUICK_LOOK_UP */

		/* A source file of some kind.  Note this may simply
		   be an included file.  */
		set_namestring (dn_bufp, &namestring, objfile);

		/* Check if this is the source file we are already working
		   with.  */
		if (pst && !strcmp (namestring, pst->filename))
		  continue;

		/* Check if this is an include file, if so check if we have
		   already seen it.  Add it to the include list */
		p = strrchr (namestring, '.');
		if (!strcmp (p, ".h"))
		  {
		    int j, found;

		    found = 0;
		    for (j = 0; j < includes_used; j++)
		      if (!strcmp (namestring, psymtab_include_list[j]))
			{
			  found = 1;
			  break;
			}
		    if (found)
		      continue;

		    /* Add it to the list of includes seen so far and
		       allocate more include space if necessary.  */
		    psymtab_include_list[includes_used++] = namestring;
		    if (includes_used >= includes_allocated)
		      {
			char **orig = psymtab_include_list;

			psymtab_include_list = (char **)
			  alloca ((includes_allocated *= 2) *
				  sizeof (char *));
			memcpy (psymtab_include_list, orig,
				includes_used * sizeof (char *));
		      }
		    continue;
		  }

		if (pst)
		  {
		    if (!have_name)
		      {
			pst->filename = (char *)
			  obstack_alloc (&pst->objfile->objfile_obstack,
					 strlen (namestring) + 1);
			strcpy (pst->filename, namestring);
			have_name = 1;
			continue;
		      }
		    continue;
		  }

		/* This is a bonafide new source file.
		   End the current partial symtab and start a new one.  */

		if (pst && past_first_source_file)
		  {
		    hpread_end_psymtab (pst, psymtab_include_list,
					includes_used,
					(hp_symnum
					 * sizeof (struct dntt_type_block)),
					texthigh,
					dependency_list, dependencies_used);
		    pst = (struct partial_symtab *) 0;
		    includes_used = 0;
		    dependencies_used = 0;
		  }
		else
		  past_first_source_file = 1;

		valu = hpread_get_textlow (i, hp_symnum, objfile, symcount);
		valu += ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile));
		pst = hpread_start_psymtab (objfile,
					    namestring, valu,
					    (hp_symnum
					 * sizeof (struct dntt_type_block)),
					    objfile->global_psymbols.next,
					    objfile->static_psymbols.next);
		texthigh = valu;
		have_name = 1;
		continue;
	      }

	    case DNTT_TYPE_MODULE:
	      /* A source file.  It's still unclear to me what the
	         real difference between a DNTT_TYPE_SRCFILE and DNTT_TYPE_MODULE
	         is supposed to be.  */

	      /* First end the previous psymtab */
	      if (pst)
		{
		  hpread_end_psymtab (pst, psymtab_include_list, includes_used,
				      ((hp_symnum - 1)
				       * sizeof (struct dntt_type_block)),
				      texthigh,
				      dependency_list, dependencies_used);
		  pst = (struct partial_symtab *) 0;
		  includes_used = 0;
		  dependencies_used = 0;
		  have_name = 0;
		}

	      /* Now begin a new module and a new psymtab for it */
	      set_namestring (dn_bufp, &namestring, objfile);
	      valu = hpread_get_textlow (i, hp_symnum, objfile, symcount);
	      valu += ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile));
	      if (!pst)
		{
		  pst = hpread_start_psymtab (objfile,
					      namestring, valu,
					      (hp_symnum
					 * sizeof (struct dntt_type_block)),
					      objfile->global_psymbols.next,
					      objfile->static_psymbols.next);
		  texthigh = valu;
		  have_name = 0;
		}
	      continue;

	    case DNTT_TYPE_FUNCTION:
	    case DNTT_TYPE_ENTRY:
	      /* The beginning of a function.  DNTT_TYPE_ENTRY may also denote
	         a secondary entry point.  */
	      valu = dn_bufp->dfunc.hiaddr + ANOFFSET (objfile->section_offsets,
						       SECT_OFF_TEXT (objfile));
	      if (valu > texthigh)
		texthigh = valu;
	      valu = dn_bufp->dfunc.lowaddr +
		ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile));
	      set_namestring (dn_bufp, &namestring, objfile);
	      if (dn_bufp->dfunc.global)
		add_psymbol_to_list (namestring, strlen (namestring),
				     VAR_DOMAIN, LOC_BLOCK,
				     &objfile->global_psymbols, valu,
				     0, language_unknown, objfile);
	      else
		add_psymbol_to_list (namestring, strlen (namestring),
				     VAR_DOMAIN, LOC_BLOCK,
				     &objfile->static_psymbols, valu,
				     0, language_unknown, objfile);
	      within_function = 1;
	      continue;

	    case DNTT_TYPE_DOC_FUNCTION:
	      valu = dn_bufp->ddocfunc.hiaddr + ANOFFSET (objfile->section_offsets,
							  SECT_OFF_TEXT (objfile));
	      if (valu > texthigh)
		texthigh = valu;
	      valu = dn_bufp->ddocfunc.lowaddr +
		ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile));
	      set_namestring (dn_bufp, &namestring, objfile);
	      if (dn_bufp->ddocfunc.global)
		add_psymbol_to_list (namestring, strlen (namestring),
				     VAR_DOMAIN, LOC_BLOCK,
				     &objfile->global_psymbols, valu,
				     0, language_unknown, objfile);
	      else
		add_psymbol_to_list (namestring, strlen (namestring),
				     VAR_DOMAIN, LOC_BLOCK,
				     &objfile->static_psymbols, valu,
				     0, language_unknown, objfile);
	      within_function = 1;
	      continue;

	    case DNTT_TYPE_BEGIN:
	    case DNTT_TYPE_END:
	      /* We don't check MODULE end here, because there can be
	         symbols beyond the module end which properly belong to the
	         current psymtab -- so we wait till the next MODULE start */


#ifdef QUICK_LOOK_UP
	      if (scan_start == hp_symnum
		  && symcount == hp_symnum + 1)
		{
		  /* If there are NO globals in an executable,
		     PXDB's index to the globals will point to
		     the last record in the file, which is
		     probably an END MODULE, i.e. this record.
		     ignore it and be done! */
		  continue;
		}
#endif /* QUICK_LOOK_UP */

	      /* Scope block begin/end.  We only care about function
	         and file blocks right now.  */

	      if ((dn_bufp->dend.endkind == DNTT_TYPE_FUNCTION) ||
		  (dn_bufp->dend.endkind == DNTT_TYPE_DOC_FUNCTION))
		within_function = 0;
	      continue;

	    case DNTT_TYPE_SVAR:
	    case DNTT_TYPE_DVAR:
	    case DNTT_TYPE_TYPEDEF:
	    case DNTT_TYPE_TAGDEF:
	      {
		/* Variables, typedefs an the like.  */
		enum address_class storage;
		domain_enum domain;

		/* Don't add locals to the partial symbol table.  */
		if (within_function
		    && (dn_bufp->dblock.kind == DNTT_TYPE_SVAR
			|| dn_bufp->dblock.kind == DNTT_TYPE_DVAR))
		  continue;

		/* TAGDEFs go into the structure domain.  */
		if (dn_bufp->dblock.kind == DNTT_TYPE_TAGDEF)
		  domain = STRUCT_DOMAIN;
		else
		  domain = VAR_DOMAIN;

		/* What kind of "storage" does this use?  */
		if (dn_bufp->dblock.kind == DNTT_TYPE_SVAR)
		  storage = LOC_STATIC;
		else if (dn_bufp->dblock.kind == DNTT_TYPE_DVAR
			 && dn_bufp->ddvar.regvar)
		  storage = LOC_REGISTER;
		else if (dn_bufp->dblock.kind == DNTT_TYPE_DVAR)
		  storage = LOC_LOCAL;
		else
		  storage = LOC_UNDEF;

		set_namestring (dn_bufp, &namestring, objfile);
		if (!pst)
		  {
		    pst = hpread_start_psymtab (objfile,
						"globals", 0,
						(hp_symnum
					 * sizeof (struct dntt_type_block)),
					      objfile->global_psymbols.next,
					     objfile->static_psymbols.next);
		  }

		/* Compute address of the data symbol */
		valu = dn_bufp->dsvar.location;
		/* Relocate in case it's in a shared library */
		if (storage == LOC_STATIC)
		  valu += ANOFFSET (objfile->section_offsets, SECT_OFF_DATA (objfile));

		/* Luckily, dvar, svar, typedef, and tagdef all
		   have their "global" bit in the same place, so it works
		   (though it's bad programming practice) to reference
		   "dsvar.global" even though we may be looking at
		   any of the above four types. */
		if (dn_bufp->dsvar.global)
		  {
		    add_psymbol_to_list (namestring, strlen (namestring),
					 domain, storage,
					 &objfile->global_psymbols,
					 valu,
					 0, language_unknown, objfile);
		  }
		else
		  {
		    add_psymbol_to_list (namestring, strlen (namestring),
					 domain, storage,
					 &objfile->static_psymbols,
					 valu,
					 0, language_unknown, objfile);
		  }

		/* For TAGDEF's, the above code added the tagname to the
		   struct domain. This will cause tag "t" to be found
		   on a reference of the form "(struct t) x". But for
		   C++ classes, "t" will also be a typename, which we
		   want to find on a reference of the form "ptype t".
		   Therefore, we also add "t" to the var domain.
		   Do the same for enum's due to the way aCC generates
		   debug info for these (see more extended comment
		   in hp-symtab-read.c).
		   We do the same for templates, so that "ptype t"
		   where "t" is a template also works. */
		if (dn_bufp->dblock.kind == DNTT_TYPE_TAGDEF &&
		  dn_bufp->dtype.type.dnttp.index < LNTT_SYMCOUNT (objfile))
		  {
		    int global = dn_bufp->dtag.global;
		    /* Look ahead to see if it's a C++ class */
		    dn_bufp = hpread_get_lntt (dn_bufp->dtype.type.dnttp.index, objfile);
		    if (dn_bufp->dblock.kind == DNTT_TYPE_CLASS ||
			dn_bufp->dblock.kind == DNTT_TYPE_ENUM ||
			dn_bufp->dblock.kind == DNTT_TYPE_TEMPLATE)
		      {
			if (global)
			  {
			    add_psymbol_to_list (namestring, strlen (namestring),
						 VAR_DOMAIN, storage,
						 &objfile->global_psymbols,
						 dn_bufp->dsvar.location,
					      0, language_unknown, objfile);
			  }
			else
			  {
			    add_psymbol_to_list (namestring, strlen (namestring),
						 VAR_DOMAIN, storage,
						 &objfile->static_psymbols,
						 dn_bufp->dsvar.location,
					      0, language_unknown, objfile);
			  }
		      }
		  }
	      }
	      continue;

	    case DNTT_TYPE_MEMENUM:
	    case DNTT_TYPE_CONST:
	      /* Constants and members of enumerated types.  */
	      set_namestring (dn_bufp, &namestring, objfile);
	      if (!pst)
		{
		  pst = hpread_start_psymtab (objfile,
					      "globals", 0,
					      (hp_symnum
					 * sizeof (struct dntt_type_block)),
					      objfile->global_psymbols.next,
					      objfile->static_psymbols.next);
		}
	      if (dn_bufp->dconst.global)
		add_psymbol_to_list (namestring, strlen (namestring),
				     VAR_DOMAIN, LOC_CONST,
				     &objfile->global_psymbols, 0,
				     0, language_unknown, objfile);
	      else
		add_psymbol_to_list (namestring, strlen (namestring),
				     VAR_DOMAIN, LOC_CONST,
				     &objfile->static_psymbols, 0,
				     0, language_unknown, objfile);
	      continue;
	    default:
	      continue;
	    }
	}
    }

  /* End any pending partial symbol table. */
  if (pst)
    {
      hpread_end_psymtab (pst, psymtab_include_list, includes_used,
			  hp_symnum * sizeof (struct dntt_type_block),
			  0, dependency_list, dependencies_used);
    }

  discard_cleanups (old_chain);
}