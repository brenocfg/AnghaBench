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
struct symbol {int dummy; } ;
struct dwarf_expr_baton {int /*<<< orphan*/  frame; } ;
struct dwarf2_loclist_baton {int dummy; } ;
struct dwarf2_locexpr_baton {size_t size; unsigned char* data; } ;

/* Variables and functions */
 void* SYMBOL_LOCATION_BATON (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_NATURAL_NAME (struct symbol*) ; 
 int /*<<< orphan*/ * SYMBOL_OPS (struct symbol*) ; 
 int /*<<< orphan*/  dwarf2_loclist_funcs ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 unsigned char* find_location_expression (struct dwarf2_loclist_baton*,size_t*,int /*<<< orphan*/ ) ; 
 struct symbol* get_frame_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_pc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwarf_expr_frame_base (void *baton, unsigned char **start, size_t * length)
{
  /* FIXME: cagney/2003-03-26: This code should be using
     get_frame_base_address(), and then implement a dwarf2 specific
     this_base method.  */
  struct symbol *framefunc;
  struct dwarf_expr_baton *debaton = (struct dwarf_expr_baton *) baton;

  framefunc = get_frame_function (debaton->frame);

  if (SYMBOL_OPS (framefunc) == &dwarf2_loclist_funcs)
    {
      struct dwarf2_loclist_baton *symbaton;
      symbaton = SYMBOL_LOCATION_BATON (framefunc);
      *start = find_location_expression (symbaton, length,
					 get_frame_pc (debaton->frame));
    }
  else
    {
      struct dwarf2_locexpr_baton *symbaton;
      symbaton = SYMBOL_LOCATION_BATON (framefunc);
      *length = symbaton->size;
      *start = symbaton->data;
    }

  if (*start == NULL)
    error ("Could not find the frame base for \"%s\".",
	   SYMBOL_NATURAL_NAME (framefunc));
}