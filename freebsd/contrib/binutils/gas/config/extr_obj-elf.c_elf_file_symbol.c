#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* bsym; } ;
typedef  TYPE_2__ symbolS ;
struct TYPE_15__ {int flags; } ;
struct TYPE_14__ {int flags; } ;

/* Variables and functions */
 int BSF_FILE ; 
 int /*<<< orphan*/  absolute_section ; 
 int /*<<< orphan*/  ecoff_new_file (char const*,int) ; 
 TYPE_12__* symbol_get_bfdsym (TYPE_2__*) ; 
 int /*<<< orphan*/  symbol_insert (TYPE_2__*,TYPE_2__*,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_lastP ; 
 TYPE_2__* symbol_new (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_remove (TYPE_2__*,TYPE_2__**,int /*<<< orphan*/ *) ; 
 TYPE_2__* symbol_rootP ; 
 int /*<<< orphan*/  symbol_set_frag (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_symbol_chain (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_address_frag ; 

void
elf_file_symbol (const char *s, int appfile)
{
  if (!appfile
      || symbol_rootP == NULL
      || symbol_rootP->bsym == NULL
      || (symbol_rootP->bsym->flags & BSF_FILE) == 0)
    {
      symbolS *sym;

      sym = symbol_new (s, absolute_section, 0, NULL);
      symbol_set_frag (sym, &zero_address_frag);
      symbol_get_bfdsym (sym)->flags |= BSF_FILE;

      if (symbol_rootP != sym)
	{
	  symbol_remove (sym, &symbol_rootP, &symbol_lastP);
	  symbol_insert (sym, symbol_rootP, &symbol_rootP, &symbol_lastP);
#ifdef DEBUG
	  verify_symbol_chain (symbol_rootP, symbol_lastP);
#endif
	}
    }

#ifdef NEED_ECOFF_DEBUG
  ecoff_new_file (s, appfile);
#endif
}