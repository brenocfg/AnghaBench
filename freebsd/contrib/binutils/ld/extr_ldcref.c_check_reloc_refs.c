#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct lang_nocrossref {char const* name; struct lang_nocrossref* next; } ;
struct check_refs_info {char* sym_name; TYPE_7__* defsec; int /*<<< orphan*/  asymbols; scalar_t__ global; TYPE_1__* ncrs; } ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_18__ {int /*<<< orphan*/  owner; struct TYPE_18__* output_section; } ;
typedef  TYPE_2__ asection ;
struct TYPE_19__ {TYPE_11__** sym_ptr_ptr; int /*<<< orphan*/  address; } ;
typedef  TYPE_3__ arelent ;
struct TYPE_20__ {TYPE_2__* output_section; } ;
struct TYPE_17__ {struct lang_nocrossref* list; } ;
struct TYPE_16__ {int flags; } ;

/* Variables and functions */
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 int BSF_SECTION_SYM ; 
 int BSF_WEAK ; 
 int /*<<< orphan*/  _ (char*) ; 
 char const* bfd_asymbol_name (TYPE_11__*) ; 
 long bfd_canonicalize_reloc (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__**,int /*<<< orphan*/ ) ; 
 long bfd_get_reloc_upper_bound (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_7__* bfd_get_section (TYPE_11__*) ; 
 char* bfd_get_section_name (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ bfd_is_com_section (TYPE_7__*) ; 
 scalar_t__ bfd_is_und_section (TYPE_7__*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  free (TYPE_3__**) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 TYPE_3__** xmalloc (long) ; 

__attribute__((used)) static void
check_reloc_refs (bfd *abfd, asection *sec, void *iarg)
{
  struct check_refs_info *info = iarg;
  asection *outsec;
  const char *outsecname;
  asection *outdefsec;
  const char *outdefsecname;
  struct lang_nocrossref *ncr;
  const char *symname;
  bfd_boolean global;
  long relsize;
  arelent **relpp;
  long relcount;
  arelent **p, **pend;

  outsec = sec->output_section;
  outsecname = bfd_get_section_name (outsec->owner, outsec);

  outdefsec = info->defsec->output_section;
  outdefsecname = bfd_get_section_name (outdefsec->owner, outdefsec);

  /* The section where the symbol is defined is permitted.  */
  if (strcmp (outsecname, outdefsecname) == 0)
    return;

  for (ncr = info->ncrs->list; ncr != NULL; ncr = ncr->next)
    if (strcmp (outsecname, ncr->name) == 0)
      break;

  if (ncr == NULL)
    return;

  /* This section is one for which cross references are prohibited.
     Look through the relocations, and see if any of them are to
     INFO->SYM_NAME.  If INFO->SYMNAME is NULL, check for relocations
     against the section symbol.  If INFO->GLOBAL is TRUE, the
     definition is global, check for relocations against the global
     symbols.  Otherwise check for relocations against the local and
     section symbols.  */

  symname = info->sym_name;
  global = info->global;

  relsize = bfd_get_reloc_upper_bound (abfd, sec);
  if (relsize < 0)
    einfo (_("%B%F: could not read relocs: %E\n"), abfd);
  if (relsize == 0)
    return;

  relpp = xmalloc (relsize);
  relcount = bfd_canonicalize_reloc (abfd, sec, relpp, info->asymbols);
  if (relcount < 0)
    einfo (_("%B%F: could not read relocs: %E\n"), abfd);

  p = relpp;
  pend = p + relcount;
  for (; p < pend && *p != NULL; p++)
    {
      arelent *q = *p;

      if (q->sym_ptr_ptr != NULL
	  && *q->sym_ptr_ptr != NULL
	  && ((global
	       && (bfd_is_und_section (bfd_get_section (*q->sym_ptr_ptr))
		   || bfd_is_com_section (bfd_get_section (*q->sym_ptr_ptr))
		   || ((*q->sym_ptr_ptr)->flags & (BSF_GLOBAL
						   | BSF_WEAK)) != 0))
	      || (!global
		  && ((*q->sym_ptr_ptr)->flags & (BSF_LOCAL
						  | BSF_SECTION_SYM)) != 0
		  && bfd_get_section (*q->sym_ptr_ptr) == info->defsec))
	  && (symname != NULL
	      ? strcmp (bfd_asymbol_name (*q->sym_ptr_ptr), symname) == 0
	      : ((*q->sym_ptr_ptr)->flags & BSF_SECTION_SYM) != 0))
	{
	  /* We found a reloc for the symbol.  The symbol is defined
	     in OUTSECNAME.  This reloc is from a section which is
	     mapped into a section from which references to OUTSECNAME
	     are prohibited.  We must report an error.  */
	  einfo (_("%X%C: prohibited cross reference from %s to `%T' in %s\n"),
		 abfd, sec, q->address, outsecname,
		 bfd_asymbol_name (*q->sym_ptr_ptr), outdefsecname);
	}
    }

  free (relpp);
}