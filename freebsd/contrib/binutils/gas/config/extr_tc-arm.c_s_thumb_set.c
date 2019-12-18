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
typedef  int /*<<< orphan*/  symbolS ;
struct list_info_struct {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fr_symbol; struct list_info_struct* line; int /*<<< orphan*/  fr_type; } ;
typedef  TYPE_1__ fragS ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SET_INTERWORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_SET_THUMB (int /*<<< orphan*/ *,int) ; 
 int LISTING_SYMBOLS ; 
 int /*<<< orphan*/  SF_SET_LOCAL (int /*<<< orphan*/ *) ; 
 char* S_GET_NAME (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THUMB_SET_FUNC (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 char get_symbol_end () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 int listing ; 
 int /*<<< orphan*/ * md_undefined_symbol (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pseudo_set (int /*<<< orphan*/ *) ; 
 scalar_t__ reg_section ; 
 int /*<<< orphan*/  rs_fill ; 
 int /*<<< orphan*/  support_interwork ; 
 int /*<<< orphan*/ * symbol_find (char*) ; 
 int /*<<< orphan*/ * symbol_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  symbol_table_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  undefined_section ; 
 TYPE_1__* xmalloc (int) ; 
 TYPE_1__ zero_address_frag ; 

__attribute__((used)) static void
s_thumb_set (int equiv)
{
  /* XXX the following is a duplicate of the code for s_set() in read.c
     We cannot just call that code as we need to get at the symbol that
     is created.  */
  char *    name;
  char	    delim;
  char *    end_name;
  symbolS * symbolP;

  /* Especial apologies for the random logic:
     This just grew, and could be parsed much more simply!
     Dean - in haste.  */
  name	    = input_line_pointer;
  delim	    = get_symbol_end ();
  end_name  = input_line_pointer;
  *end_name = delim;

  if (*input_line_pointer != ',')
    {
      *end_name = 0;
      as_bad (_("expected comma after name \"%s\""), name);
      *end_name = delim;
      ignore_rest_of_line ();
      return;
    }

  input_line_pointer++;
  *end_name = 0;

  if (name[0] == '.' && name[1] == '\0')
    {
      /* XXX - this should not happen to .thumb_set.  */
      abort ();
    }

  if ((symbolP = symbol_find (name)) == NULL
      && (symbolP = md_undefined_symbol (name)) == NULL)
    {
#ifndef NO_LISTING
      /* When doing symbol listings, play games with dummy fragments living
	 outside the normal fragment chain to record the file and line info
	 for this symbol.  */
      if (listing & LISTING_SYMBOLS)
	{
	  extern struct list_info_struct * listing_tail;
	  fragS * dummy_frag = xmalloc (sizeof (fragS));

	  memset (dummy_frag, 0, sizeof (fragS));
	  dummy_frag->fr_type = rs_fill;
	  dummy_frag->line = listing_tail;
	  symbolP = symbol_new (name, undefined_section, 0, dummy_frag);
	  dummy_frag->fr_symbol = symbolP;
	}
      else
#endif
	symbolP = symbol_new (name, undefined_section, 0, &zero_address_frag);

#ifdef OBJ_COFF
      /* "set" symbols are local unless otherwise specified.  */
      SF_SET_LOCAL (symbolP);
#endif /* OBJ_COFF  */
    }				/* Make a new symbol.  */

  symbol_table_insert (symbolP);

  * end_name = delim;

  if (equiv
      && S_IS_DEFINED (symbolP)
      && S_GET_SEGMENT (symbolP) != reg_section)
    as_bad (_("symbol `%s' already defined"), S_GET_NAME (symbolP));

  pseudo_set (symbolP);

  demand_empty_rest_of_line ();

  /* XXX Now we come to the Thumb specific bit of code.	 */

  THUMB_SET_FUNC (symbolP, 1);
  ARM_SET_THUMB (symbolP, 1);
#if defined OBJ_ELF || defined OBJ_COFF
  ARM_SET_INTERWORK (symbolP, support_interwork);
#endif
}