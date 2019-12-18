#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {struct TYPE_21__* sy_next; struct TYPE_21__* sy_previous; TYPE_2__* bsym; } ;
typedef  TYPE_1__ symbolS ;
struct local_symbol {int dummy; } ;
struct TYPE_22__ {int /*<<< orphan*/  section; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ asymbol ;

/* Variables and functions */
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_1__*) ; 
 int /*<<< orphan*/  as_fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_asymbol_bfd (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_copy_private_symbol_data (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 TYPE_2__* bfd_make_empty_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_verify_symchain (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* local_symbol_convert (struct local_symbol*) ; 
 int /*<<< orphan*/  notes ; 
 int /*<<< orphan*/  obj_symbol_clone_hook (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* obstack_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* symbol_lastP ; 
 TYPE_1__* symbol_rootP ; 
 int /*<<< orphan*/  symbol_table_insert (TYPE_1__*) ; 
 int /*<<< orphan*/  tc_symbol_clone_hook (TYPE_1__*,TYPE_1__*) ; 

symbolS *
symbol_clone (symbolS *orgsymP, int replace)
{
  symbolS *newsymP;
  asymbol *bsymorg, *bsymnew;

  /* Running local_symbol_convert on a clone that's not the one currently
     in local_hash would incorrectly replace the hash entry.  Thus the
     symbol must be converted here.  Note that the rest of the function
     depends on not encountering an unconverted symbol.  */
  if (LOCAL_SYMBOL_CHECK (orgsymP))
    orgsymP = local_symbol_convert ((struct local_symbol *) orgsymP);
  bsymorg = orgsymP->bsym;

  newsymP = obstack_alloc (&notes, sizeof (*newsymP));
  *newsymP = *orgsymP;
  bsymnew = bfd_make_empty_symbol (bfd_asymbol_bfd (bsymorg));
  if (bsymnew == NULL)
    as_fatal ("bfd_make_empty_symbol: %s", bfd_errmsg (bfd_get_error ()));
  newsymP->bsym = bsymnew;
  bsymnew->name = bsymorg->name;
  bsymnew->flags =  bsymorg->flags;
  bsymnew->section =  bsymorg->section;
  bfd_copy_private_symbol_data (bfd_asymbol_bfd (bsymorg), bsymorg,
				bfd_asymbol_bfd (bsymnew), bsymnew);

#ifdef obj_symbol_clone_hook
  obj_symbol_clone_hook (newsymP, orgsymP);
#endif

#ifdef tc_symbol_clone_hook
  tc_symbol_clone_hook (newsymP, orgsymP);
#endif

  if (replace)
    {
      if (symbol_rootP == orgsymP)
	symbol_rootP = newsymP;
      else if (orgsymP->sy_previous)
	{
	  orgsymP->sy_previous->sy_next = newsymP;
	  orgsymP->sy_previous = NULL;
	}
      if (symbol_lastP == orgsymP)
	symbol_lastP = newsymP;
      else if (orgsymP->sy_next)
	orgsymP->sy_next->sy_previous = newsymP;
      orgsymP->sy_previous = orgsymP->sy_next = orgsymP;
      debug_verify_symchain (symbol_rootP, symbol_lastP);

      symbol_table_insert (newsymP);
    }
  else
    newsymP->sy_previous = newsymP->sy_next = newsymP;

  return newsymP;
}