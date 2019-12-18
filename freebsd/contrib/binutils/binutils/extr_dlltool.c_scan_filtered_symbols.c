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
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ asymbol ;

/* Variables and functions */
 int BSF_FUNCTION ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ add_stdcall_alias ; 
 char* bfd_asymbol_name (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 char const bfd_get_symbol_leading_char (int /*<<< orphan*/ *) ; 
 TYPE_1__* bfd_make_empty_symbol (int /*<<< orphan*/ *) ; 
 TYPE_1__* bfd_minisymbol_to_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  def_exports (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
scan_filtered_symbols (bfd *abfd, void *minisyms, long symcount,
		       unsigned int size)
{
  asymbol *store;
  bfd_byte *from, *fromend;

  store = bfd_make_empty_symbol (abfd);
  if (store == NULL)
    bfd_fatal (bfd_get_filename (abfd));

  from = (bfd_byte *) minisyms;
  fromend = from + symcount * size;
  for (; from < fromend; from += size)
    {
      asymbol *sym;
      const char *symbol_name;

      sym = bfd_minisymbol_to_symbol (abfd, FALSE, from, store);
      if (sym == NULL)
	bfd_fatal (bfd_get_filename (abfd));

      symbol_name = bfd_asymbol_name (sym);
      if (bfd_get_symbol_leading_char (abfd) == symbol_name[0])
	++symbol_name;

      def_exports (xstrdup (symbol_name) , 0, -1, 0, 0,
		   ! (sym->flags & BSF_FUNCTION), 0);

      if (add_stdcall_alias && strchr (symbol_name, '@'))
        {
	  int lead_at = (*symbol_name == '@');
	  char *exported_name = xstrdup (symbol_name + lead_at);
	  char *atsym = strchr (exported_name, '@');
	  *atsym = '\0';
	  /* Note: stdcall alias symbols can never be data.  */
	  def_exports (exported_name, xstrdup (symbol_name), -1, 0, 0, 0, 0);
	}
    }
}