#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  section; } ;
typedef  TYPE_1__ asymbol ;

/* Variables and functions */
 int BSF_GLOBAL ; 
 int BSF_WEAK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_is_com_section (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_is_und_section (int /*<<< orphan*/ ) ; 
 TYPE_1__* bfd_make_empty_symbol (int /*<<< orphan*/ *) ; 
 TYPE_1__* bfd_minisymbol_to_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,TYPE_1__*) ; 
 int /*<<< orphan*/  match_exclude (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static long
filter_symbols (bfd *abfd, void *minisyms, long symcount, unsigned int size)
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

      sym = bfd_minisymbol_to_symbol (abfd, FALSE, (const void *) from, store);
      if (sym == NULL)
	bfd_fatal (bfd_get_filename (abfd));

      /* Check for external and defined only symbols.  */
      keep = (((sym->flags & BSF_GLOBAL) != 0
	       || (sym->flags & BSF_WEAK) != 0
	       || bfd_is_com_section (sym->section))
	      && ! bfd_is_und_section (sym->section));

      keep = keep && ! match_exclude (sym->name);

      if (keep)
	{
	  memcpy (to, from, size);
	  to += size;
	}
    }

  return (to - (bfd_byte *) minisyms) / size;
}