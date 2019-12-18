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
typedef  char* tree ;
typedef  int /*<<< orphan*/  conversion ;

/* Variables and functions */
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 char* TREE_TYPE (char*) ; 
 char* build_nop (char*,char*) ; 
 int /*<<< orphan*/  conversion_obstack ; 
 void* conversion_obstack_alloc (int /*<<< orphan*/ ) ; 
 char* convert_like (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 char* error_mark_node ; 
 scalar_t__ error_operand_p (char*) ; 
 int /*<<< orphan*/ * implicit_conversion (char*,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ processing_template_decl ; 

tree
perform_implicit_conversion (tree type, tree expr)
{
  conversion *conv;
  void *p;

  if (error_operand_p (expr))
    return error_mark_node;

  /* Get the high-water mark for the CONVERSION_OBSTACK.  */
  p = conversion_obstack_alloc (0);

  conv = implicit_conversion (type, TREE_TYPE (expr), expr,
			      /*c_cast_p=*/false,
			      LOOKUP_NORMAL);
  if (!conv)
    {
      error ("could not convert %qE to %qT", expr, type);
      expr = error_mark_node;
    }
  else if (processing_template_decl)
    {
      /* In a template, we are only concerned about determining the
	 type of non-dependent expressions, so we do not have to
	 perform the actual conversion.  */
      if (TREE_TYPE (expr) != type)
	expr = build_nop (type, expr);
    }
  else
    expr = convert_like (conv, expr);

  /* Free all the conversions we allocated.  */
  obstack_free (&conversion_obstack, p);

  return expr;
}