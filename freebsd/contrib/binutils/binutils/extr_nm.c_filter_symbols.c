#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  section; } ;
typedef  TYPE_1__ asymbol ;

/* Variables and functions */
 int BSF_DEBUGGING ; 
 int BSF_GLOBAL ; 
 int BSF_WEAK ; 
 int /*<<< orphan*/  PROGRESS (int) ; 
 int /*<<< orphan*/  allow_special_symbols ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_is_abs_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_is_com_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_is_target_special_symbol (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int bfd_is_und_section (int /*<<< orphan*/ ) ; 
 TYPE_1__* bfd_make_empty_symbol (int /*<<< orphan*/ *) ; 
 TYPE_1__* bfd_minisymbol_to_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,TYPE_1__*) ; 
 scalar_t__ defined_only ; 
 scalar_t__ external_only ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  print_debug_syms ; 
 scalar_t__ sort_by_size ; 
 scalar_t__ undefined_only ; 

__attribute__((used)) static long
filter_symbols (bfd *abfd, bfd_boolean dynamic, void *minisyms,
		long symcount, unsigned int size)
{
  bfd_byte *from, *fromend, *to;
  asymbol *store;

  store = bfd_make_empty_symbol (abfd);
  if (store == NULL)
    bfd_fatal (bfd_get_filename (abfd));

  from = (bfd_byte *) minisyms;
  fromend = from + symcount * size;
  to = (bfd_byte *) minisyms;

  for (; from < fromend; from += size)
    {
      int keep = 0;
      asymbol *sym;

      PROGRESS (1);

      sym = bfd_minisymbol_to_symbol (abfd, dynamic, (const void *) from, store);
      if (sym == NULL)
	bfd_fatal (bfd_get_filename (abfd));

      if (undefined_only)
	keep = bfd_is_und_section (sym->section);
      else if (external_only)
	keep = ((sym->flags & BSF_GLOBAL) != 0
		|| (sym->flags & BSF_WEAK) != 0
		|| bfd_is_und_section (sym->section)
		|| bfd_is_com_section (sym->section));
      else
	keep = 1;

      if (keep
	  && ! print_debug_syms
	  && (sym->flags & BSF_DEBUGGING) != 0)
	keep = 0;

      if (keep
	  && sort_by_size
	  && (bfd_is_abs_section (sym->section)
	      || bfd_is_und_section (sym->section)))
	keep = 0;

      if (keep
	  && defined_only)
	{
	  if (bfd_is_und_section (sym->section))
	    keep = 0;
	}

      if (keep
	  && bfd_is_target_special_symbol (abfd, sym)
	  && ! allow_special_symbols)
	keep = 0;

      if (keep)
	{
	  memcpy (to, from, size);
	  to += size;
	}
    }

  return (to - (bfd_byte *) minisyms) / size;
}