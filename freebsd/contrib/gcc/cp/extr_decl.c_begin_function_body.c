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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  BCS_FN_BODY ; 
 scalar_t__ DECL_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUNCTION_NEEDS_BODY_BLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  begin_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  begin_destructor_body () ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  keep_next_level (int) ; 
 scalar_t__ processing_template_decl ; 

tree
begin_function_body (void)
{
  tree stmt;

  if (! FUNCTION_NEEDS_BODY_BLOCK (current_function_decl))
    return NULL_TREE;

  if (processing_template_decl)
    /* Do nothing now.  */;
  else
    /* Always keep the BLOCK node associated with the outermost pair of
       curly braces of a function.  These are needed for correct
       operation of dwarfout.c.  */
    keep_next_level (true);

  stmt = begin_compound_stmt (BCS_FN_BODY);

  if (processing_template_decl)
    /* Do nothing now.  */;
  else if (DECL_DESTRUCTOR_P (current_function_decl))
    begin_destructor_body ();

  return stmt;
}