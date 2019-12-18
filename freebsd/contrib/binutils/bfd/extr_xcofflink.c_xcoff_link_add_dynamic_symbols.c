#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_13__ ;

/* Type definitions */
struct TYPE_27__ {int /*<<< orphan*/  value; void* section; } ;
struct TYPE_31__ {TYPE_8__* abfd; } ;
struct TYPE_32__ {TYPE_1__ def; TYPE_5__ undef; } ;
struct TYPE_33__ {scalar_t__ type; TYPE_6__ u; } ;
struct xcoff_link_hash_entry {int flags; scalar_t__ smclas; TYPE_7__ root; struct xcoff_link_hash_entry* descriptor; } ;
struct xcoff_import_file {char* path; char const* file; char const* member; struct xcoff_import_file* next; } ;
struct TYPE_29__ {scalar_t__ _l_zeroes; int _l_offset; } ;
struct TYPE_30__ {int /*<<< orphan*/  _l_name; TYPE_3__ _l_l; } ;
struct internal_ldsym {int l_smtype; scalar_t__ l_smclas; int /*<<< orphan*/  l_value; TYPE_4__ _l; } ;
struct internal_ldhdr {int l_stoff; int l_nsyms; } ;
struct bfd_link_info {TYPE_2__* hash; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  char bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_34__ {scalar_t__ xvec; int flags; struct TYPE_34__* my_archive; } ;
typedef  TYPE_8__ bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_35__ {struct xcoff_import_file* imports; } ;
struct TYPE_28__ {scalar_t__ creator; } ;
struct TYPE_26__ {char* contents; int /*<<< orphan*/  keep_contents; } ;
struct TYPE_25__ {unsigned int import_file_id; } ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  FALSE ; 
 int L_EXPORT ; 
 int SYMNMLEN ; 
 int /*<<< orphan*/  TRUE ; 
 int XCOFF_DEF_DYNAMIC ; 
 int XCOFF_DESCRIPTOR ; 
 scalar_t__ XMC_DS ; 
 scalar_t__ XMC_PR ; 
 scalar_t__ XMC_UA ; 
 scalar_t__ XMC_XO ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,char*) ; 
 void* bfd_abs_section_ptr ; 
 struct xcoff_import_file* bfd_alloc (TYPE_8__*,scalar_t__) ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_error_no_symbols ; 
 char* bfd_get_filename (TYPE_8__*) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (TYPE_8__*,char*) ; 
 void* bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_new ; 
 scalar_t__ bfd_link_hash_undefined ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 char* bfd_malloc (scalar_t__) ; 
 int /*<<< orphan*/  bfd_section_list_clear (TYPE_8__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int bfd_xcoff_ldsymsz (TYPE_8__*) ; 
 int bfd_xcoff_loader_symbol_offset (TYPE_8__*,struct internal_ldhdr*) ; 
 int /*<<< orphan*/  bfd_xcoff_swap_ldhdr_in (TYPE_8__*,char*,struct internal_ldhdr*) ; 
 int /*<<< orphan*/  bfd_xcoff_swap_ldsym_in (TYPE_8__*,char*,struct internal_ldsym*) ; 
 TYPE_15__* coff_section_data (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 TYPE_13__* xcoff_data (TYPE_8__*) ; 
 int /*<<< orphan*/  xcoff_get_section_contents (TYPE_8__*,int /*<<< orphan*/ *) ; 
 TYPE_9__* xcoff_hash_table (struct bfd_link_info*) ; 
 struct xcoff_link_hash_entry* xcoff_link_hash_lookup (TYPE_9__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
xcoff_link_add_dynamic_symbols (bfd *abfd, struct bfd_link_info *info)
{
  asection *lsec;
  bfd_byte *contents;
  struct internal_ldhdr ldhdr;
  const char *strings;
  bfd_byte *elsym, *elsymend;
  struct xcoff_import_file *n;
  const char *bname;
  const char *mname;
  const char *s;
  unsigned int c;
  struct xcoff_import_file **pp;

  /* We can only handle a dynamic object if we are generating an XCOFF
     output file.  */
   if (info->hash->creator != abfd->xvec)
    {
      (*_bfd_error_handler)
	(_("%s: XCOFF shared object when not producing XCOFF output"),
	 bfd_get_filename (abfd));
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  /* The symbols we use from a dynamic object are not the symbols in
     the normal symbol table, but, rather, the symbols in the export
     table.  If there is a global symbol in a dynamic object which is
     not in the export table, the loader will not be able to find it,
     so we don't want to find it either.  Also, on AIX 4.1.3, shr.o in
     libc.a has symbols in the export table which are not in the
     symbol table.  */

  /* Read in the .loader section.  FIXME: We should really use the
     o_snloader field in the a.out header, rather than grabbing the
     section by name.  */
  lsec = bfd_get_section_by_name (abfd, ".loader");
  if (lsec == NULL)
    {
      (*_bfd_error_handler)
	(_("%s: dynamic object with no .loader section"),
	 bfd_get_filename (abfd));
      bfd_set_error (bfd_error_no_symbols);
      return FALSE;
    }

  if (! xcoff_get_section_contents (abfd, lsec))
    return FALSE;
  contents = coff_section_data (abfd, lsec)->contents;

  /* Remove the sections from this object, so that they do not get
     included in the link.  */
  bfd_section_list_clear (abfd);

  bfd_xcoff_swap_ldhdr_in (abfd, contents, &ldhdr);

  strings = (char *) contents + ldhdr.l_stoff;

  elsym = contents + bfd_xcoff_loader_symbol_offset(abfd, &ldhdr);

  elsymend = elsym + ldhdr.l_nsyms * bfd_xcoff_ldsymsz(abfd);

  for (; elsym < elsymend; elsym += bfd_xcoff_ldsymsz(abfd))
    {
      struct internal_ldsym ldsym;
      char nambuf[SYMNMLEN + 1];
      const char *name;
      struct xcoff_link_hash_entry *h;

      bfd_xcoff_swap_ldsym_in (abfd, elsym, &ldsym);

      /* We are only interested in exported symbols.  */
      if ((ldsym.l_smtype & L_EXPORT) == 0)
	continue;

      if (ldsym._l._l_l._l_zeroes == 0)
	name = strings + ldsym._l._l_l._l_offset;
      else
	{
	  memcpy (nambuf, ldsym._l._l_name, SYMNMLEN);
	  nambuf[SYMNMLEN] = '\0';
	  name = nambuf;
	}

      /* Normally we could not call xcoff_link_hash_lookup in an add
	 symbols routine, since we might not be using an XCOFF hash
	 table.  However, we verified above that we are using an XCOFF
	 hash table.  */

      h = xcoff_link_hash_lookup (xcoff_hash_table (info), name, TRUE,
				  TRUE, TRUE);
      if (h == NULL)
	return FALSE;

      h->flags |= XCOFF_DEF_DYNAMIC;

      /* If the symbol is undefined, and the BFD it was found in is
	 not a dynamic object, change the BFD to this dynamic object,
	 so that we can get the correct import file ID.  */
      if ((h->root.type == bfd_link_hash_undefined
	   || h->root.type == bfd_link_hash_undefweak)
	  && (h->root.u.undef.abfd == NULL
	      || (h->root.u.undef.abfd->flags & DYNAMIC) == 0))
	h->root.u.undef.abfd = abfd;

      if (h->root.type == bfd_link_hash_new)
	{
	  h->root.type = bfd_link_hash_undefined;
	  h->root.u.undef.abfd = abfd;
	  /* We do not want to add this to the undefined symbol list.  */
	}

      if (h->smclas == XMC_UA
	  || h->root.type == bfd_link_hash_undefined
	  || h->root.type == bfd_link_hash_undefweak)
	h->smclas = ldsym.l_smclas;

      /* Unless this is an XMC_XO symbol, we don't bother to actually
	 define it, since we don't have a section to put it in anyhow.
	 Instead, the relocation routines handle the DEF_DYNAMIC flag
	 correctly.  */

      if (h->smclas == XMC_XO
	  && (h->root.type == bfd_link_hash_undefined
	      || h->root.type == bfd_link_hash_undefweak))
	{
	  /* This symbol has an absolute value.  */
	  h->root.type = bfd_link_hash_defined;
	  h->root.u.def.section = bfd_abs_section_ptr;
	  h->root.u.def.value = ldsym.l_value;
	}

      /* If this symbol defines a function descriptor, then it
	 implicitly defines the function code as well.  */
      if (h->smclas == XMC_DS
	  || (h->smclas == XMC_XO && name[0] != '.'))
	h->flags |= XCOFF_DESCRIPTOR;
      if ((h->flags & XCOFF_DESCRIPTOR) != 0)
	{
	  struct xcoff_link_hash_entry *hds;

	  hds = h->descriptor;
	  if (hds == NULL)
	    {
	      char *dsnm;

	      dsnm = bfd_malloc ((bfd_size_type) strlen (name) + 2);
	      if (dsnm == NULL)
		return FALSE;
	      dsnm[0] = '.';
	      strcpy (dsnm + 1, name);
	      hds = xcoff_link_hash_lookup (xcoff_hash_table (info), dsnm,
					    TRUE, TRUE, TRUE);
	      free (dsnm);
	      if (hds == NULL)
		return FALSE;

	      if (hds->root.type == bfd_link_hash_new)
		{
		  hds->root.type = bfd_link_hash_undefined;
		  hds->root.u.undef.abfd = abfd;
		  /* We do not want to add this to the undefined
		     symbol list.  */
		}

	      hds->descriptor = h;
	      h->descriptor = hds;
	    }

	  hds->flags |= XCOFF_DEF_DYNAMIC;
	  if (hds->smclas == XMC_UA)
	    hds->smclas = XMC_PR;

	  /* An absolute symbol appears to actually define code, not a
	     function descriptor.  This is how some math functions are
	     implemented on AIX 4.1.  */
	  if (h->smclas == XMC_XO
	      && (hds->root.type == bfd_link_hash_undefined
		  || hds->root.type == bfd_link_hash_undefweak))
	    {
	      hds->smclas = XMC_XO;
	      hds->root.type = bfd_link_hash_defined;
	      hds->root.u.def.section = bfd_abs_section_ptr;
	      hds->root.u.def.value = ldsym.l_value;
	    }
	}
    }

  if (contents != NULL && ! coff_section_data (abfd, lsec)->keep_contents)
    {
      free (coff_section_data (abfd, lsec)->contents);
      coff_section_data (abfd, lsec)->contents = NULL;
    }

  /* Record this file in the import files.  */
  n = bfd_alloc (abfd, (bfd_size_type) sizeof (struct xcoff_import_file));
  if (n == NULL)
    return FALSE;
  n->next = NULL;

  /* For some reason, the path entry in the import file list for a
     shared object appears to always be empty.  The file name is the
     base name.  */
  n->path = "";
  if (abfd->my_archive == NULL)
    {
      bname = bfd_get_filename (abfd);
      mname = "";
    }
  else
    {
      bname = bfd_get_filename (abfd->my_archive);
      mname = bfd_get_filename (abfd);
    }
  s = strrchr (bname, '/');
  if (s != NULL)
    bname = s + 1;
  n->file = bname;
  n->member = mname;

  /* We start c at 1 because the first import file number is reserved
     for LIBPATH.  */
  for (pp = &xcoff_hash_table (info)->imports, c = 1;
       *pp != NULL;
       pp = &(*pp)->next, ++c)
    ;
  *pp = n;

  xcoff_data (abfd)->import_file_id = c;

  return TRUE;
}