#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_lineno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int coff_line_base ; 
 int /*<<< orphan*/ * current_lineno_sym ; 
 int /*<<< orphan*/ * def_symbol_in_progress ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  frag_now ; 
 int /*<<< orphan*/  frag_now_fix () ; 
 int get_absolute_expression () ; 
 int /*<<< orphan*/  listing_source_line (int) ; 
 int /*<<< orphan*/  new_logical_line (char*,int) ; 

__attribute__((used)) static void
obj_coff_ln (int appline)
{
  int l;

  if (! appline && def_symbol_in_progress != NULL)
    {
      as_warn (_(".ln pseudo-op inside .def/.endef: ignored."));
      demand_empty_rest_of_line ();
      return;
    }

  l = get_absolute_expression ();

  /* If there is no lineno symbol, treat a .ln
     directive as if it were a .appline directive.  */
  if (appline || current_lineno_sym == NULL)
    new_logical_line ((char *) NULL, l - 1);
  else
    add_lineno (frag_now, frag_now_fix (), l);

#ifndef NO_LISTING
  {
    extern int listing;

    if (listing)
      {
	if (! appline)
	  l += coff_line_base - 1;
	listing_source_line (l);
      }
  }
#endif

  demand_empty_rest_of_line ();
}