#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct lang_nocrossrefs {int dummy; } ;
struct check_refs_info {char const* sym_name; int /*<<< orphan*/ ** asymbols; struct lang_nocrossrefs* ncrs; int /*<<< orphan*/ * defsec; int /*<<< orphan*/  global; } ;
struct TYPE_8__ {long symbol_count; int /*<<< orphan*/ ** asymbols; } ;
typedef  TYPE_1__ lang_input_statement_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {TYPE_1__* usrdata; } ;
typedef  TYPE_2__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 long bfd_canonicalize_symtab (TYPE_2__*,int /*<<< orphan*/ **) ; 
 long bfd_get_symtab_upper_bound (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_map_over_sections (TYPE_2__*,int /*<<< orphan*/ ,struct check_refs_info*) ; 
 int /*<<< orphan*/  check_reloc_refs ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** xmalloc (long) ; 

__attribute__((used)) static void
check_refs (const char *name,
	    bfd_boolean global,
	    asection *sec,
	    bfd *abfd,
	    struct lang_nocrossrefs *ncrs)
{
  lang_input_statement_type *li;
  asymbol **asymbols;
  struct check_refs_info info;

  /* We need to look through the relocations for this BFD, to see
     if any of the relocations which refer to this symbol are from
     a prohibited section.  Note that we need to do this even for
     the BFD in which the symbol is defined, since even a single
     BFD might contain a prohibited cross reference.  */

  li = abfd->usrdata;
  if (li != NULL && li->asymbols != NULL)
    asymbols = li->asymbols;
  else
    {
      long symsize;
      long symbol_count;

      symsize = bfd_get_symtab_upper_bound (abfd);
      if (symsize < 0)
	einfo (_("%B%F: could not read symbols; %E\n"), abfd);
      asymbols = xmalloc (symsize);
      symbol_count = bfd_canonicalize_symtab (abfd, asymbols);
      if (symbol_count < 0)
	einfo (_("%B%F: could not read symbols: %E\n"), abfd);
      if (li != NULL)
	{
	  li->asymbols = asymbols;
	  li->symbol_count = symbol_count;
	}
    }

  info.sym_name = name;
  info.global = global;
  info.defsec = sec;
  info.ncrs = ncrs;
  info.asymbols = asymbols;
  bfd_map_over_sections (abfd, check_reloc_refs, &info);

  if (li == NULL)
    free (asymbols);
}