#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct list_info_struct {int dummy; } ;
typedef  int /*<<< orphan*/  segT ;
struct TYPE_3__ {int /*<<< orphan*/ * fr_symbol; struct list_info_struct* line; } ;
typedef  TYPE_1__ fragS ;
typedef  int /*<<< orphan*/  expressionS ;

/* Variables and functions */
 int LISTING_SYMBOLS ; 
 int /*<<< orphan*/  SF_SET_LOCAL (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_VOLATILE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_FORWARD_REF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_VOLATILE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_org (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_known_segmented_expression (int /*<<< orphan*/ *) ; 
 int listing ; 
 int /*<<< orphan*/ * md_undefined_symbol (char*) ; 
 int /*<<< orphan*/  need_pass_2 ; 
 int /*<<< orphan*/  pseudo_set (int /*<<< orphan*/ *) ; 
 scalar_t__ reg_section ; 
 int /*<<< orphan*/ * symbol_clone (int /*<<< orphan*/ *,int) ; 
 scalar_t__ symbol_equated_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_find (char*) ; 
 int /*<<< orphan*/ * symbol_find_or_make (char*) ; 
 int /*<<< orphan*/  symbol_set_frag (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ xcalloc (int,int) ; 

__attribute__((used)) static void
assign_symbol (char *name, int mode)
{
  symbolS *symbolP;

  if (name[0] == '.' && name[1] == '\0')
    {
      /* Turn '. = mumble' into a .org mumble.  */
      segT segment;
      expressionS exp;

      segment = get_known_segmented_expression (&exp);

      if (!need_pass_2)
	do_org (segment, &exp, 0);

      return;
    }

  if ((symbolP = symbol_find (name)) == NULL
      && (symbolP = md_undefined_symbol (name)) == NULL)
    {
      symbolP = symbol_find_or_make (name);
#ifndef NO_LISTING
      /* When doing symbol listings, play games with dummy fragments living
	 outside the normal fragment chain to record the file and line info
	 for this symbol.  */
      if (listing & LISTING_SYMBOLS)
	{
	  extern struct list_info_struct *listing_tail;
	  fragS *dummy_frag = (fragS *) xcalloc (1, sizeof (fragS));
	  dummy_frag->line = listing_tail;
	  dummy_frag->fr_symbol = symbolP;
	  symbol_set_frag (symbolP, dummy_frag);
	}
#endif
#ifdef OBJ_COFF
      /* "set" symbols are local unless otherwise specified.  */
      SF_SET_LOCAL (symbolP);
#endif
    }

  if (S_IS_DEFINED (symbolP) || symbol_equated_p (symbolP))
    {
      /* Permit register names to be redefined.  */
      if ((mode != 0 || !S_IS_VOLATILE (symbolP))
	  && S_GET_SEGMENT (symbolP) != reg_section)
	{
	  as_bad (_("symbol `%s' is already defined"), name);
	  symbolP = symbol_clone (symbolP, 0);
	}
      /* If the symbol is volatile, copy the symbol and replace the
	 original with the copy, so that previous uses of the symbol will
	 retain the value of the symbol at the point of use.  */
      else if (S_IS_VOLATILE (symbolP))
	symbolP = symbol_clone (symbolP, 1);
    }

  if (mode == 0)
    S_SET_VOLATILE (symbolP);
  else if (mode < 0)
    S_SET_FORWARD_REF (symbolP);

  pseudo_set (symbolP);
}