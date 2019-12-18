#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct conditional_frame {int ignoring; TYPE_1__* previous_cframe; scalar_t__ dead_tree; } ;
typedef  int /*<<< orphan*/  cframe ;
struct TYPE_2__ {int /*<<< orphan*/  ignoring; } ;

/* Variables and functions */
 scalar_t__ LISTING_SKIP_COND () ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_obstack ; 
 struct conditional_frame* current_cframe ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 char get_symbol_end () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 int /*<<< orphan*/  initialize_cframe (struct conditional_frame*) ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  is_name_beginner (char) ; 
 int /*<<< orphan*/  listing_list (int) ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ obstack_copy (int /*<<< orphan*/ *,struct conditional_frame*,int) ; 
 scalar_t__ reg_section ; 
 scalar_t__ symbol_equated_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_find (char*) ; 

void
s_ifdef (int test_defined)
{
  /* Points to name of symbol.  */
  char *name;
  /* Points to symbol.  */
  symbolS *symbolP;
  struct conditional_frame cframe;
  char c;

  /* Leading whitespace is part of operand.  */
  SKIP_WHITESPACE ();
  name = input_line_pointer;

  if (!is_name_beginner (*name))
    {
      as_bad (_("invalid identifier for \".ifdef\""));
      obstack_1grow (&cond_obstack, 0);
      ignore_rest_of_line ();
      return;
    }

  c = get_symbol_end ();
  symbolP = symbol_find (name);
  *input_line_pointer = c;

  initialize_cframe (&cframe);
  
  if (cframe.dead_tree)
    cframe.ignoring = 1;
  else
    {
      int is_defined;

      /* Use the same definition of 'defined' as .equiv so that a symbol
	 which has been referenced but not yet given a value/address is
	 considered to be undefined.  */
      is_defined =
	symbolP != NULL
	&& (S_IS_DEFINED (symbolP) || symbol_equated_p (symbolP))
	&& S_GET_SEGMENT (symbolP) != reg_section;

      cframe.ignoring = ! (test_defined ^ is_defined);
    }

  current_cframe = ((struct conditional_frame *)
		    obstack_copy (&cond_obstack, &cframe,
				  sizeof (cframe)));

  if (LISTING_SKIP_COND ()
      && cframe.ignoring
      && (cframe.previous_cframe == NULL
	  || ! cframe.previous_cframe->ignoring))
    listing_list (2);

  demand_empty_rest_of_line ();
}