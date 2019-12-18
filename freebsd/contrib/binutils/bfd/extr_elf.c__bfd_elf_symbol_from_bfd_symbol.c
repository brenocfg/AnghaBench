#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_9__ {int i; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  name; TYPE_2__ udata; TYPE_4__* section; } ;
typedef  TYPE_3__ asymbol ;
struct TYPE_11__ {int index; int /*<<< orphan*/ * owner; struct TYPE_11__* output_section; } ;
typedef  TYPE_4__ asection ;
struct TYPE_8__ {int i; } ;
struct TYPE_12__ {TYPE_1__ udata; } ;

/* Variables and functions */
 int BSF_SECTION_SYM ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_asymbol_name (TYPE_3__*) ; 
 int /*<<< orphan*/  bfd_error_no_symbols ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int elf_num_section_syms (int /*<<< orphan*/ *) ; 
 TYPE_5__** elf_section_syms (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_symbol_flags (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
_bfd_elf_symbol_from_bfd_symbol (bfd *abfd, asymbol **asym_ptr_ptr)
{
  asymbol *asym_ptr = *asym_ptr_ptr;
  int idx;
  flagword flags = asym_ptr->flags;

  /* When gas creates relocations against local labels, it creates its
     own symbol for the section, but does put the symbol into the
     symbol chain, so udata is 0.  When the linker is generating
     relocatable output, this section symbol may be for one of the
     input sections rather than the output section.  */
  if (asym_ptr->udata.i == 0
      && (flags & BSF_SECTION_SYM)
      && asym_ptr->section)
    {
      asection *sec;
      int indx;

      sec = asym_ptr->section;
      if (sec->owner != abfd && sec->output_section != NULL)
	sec = sec->output_section;
      if (sec->owner == abfd
	  && (indx = sec->index) < elf_num_section_syms (abfd)
	  && elf_section_syms (abfd)[indx] != NULL)
	asym_ptr->udata.i = elf_section_syms (abfd)[indx]->udata.i;
    }

  idx = asym_ptr->udata.i;

  if (idx == 0)
    {
      /* This case can occur when using --strip-symbol on a symbol
	 which is used in a relocation entry.  */
      (*_bfd_error_handler)
	(_("%B: symbol `%s' required but not present"),
	 abfd, bfd_asymbol_name (asym_ptr));
      bfd_set_error (bfd_error_no_symbols);
      return -1;
    }

#if DEBUG & 4
  {
    fprintf (stderr,
	     "elf_symbol_from_bfd_symbol 0x%.8lx, name = %s, sym num = %d, flags = 0x%.8lx%s\n",
	     (long) asym_ptr, asym_ptr->name, idx, flags,
	     elf_symbol_flags (flags));
    fflush (stderr);
  }
#endif

  return idx;
}