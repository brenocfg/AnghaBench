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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  finish_compound_stmt (scalar_t__) ; 
 int /*<<< orphan*/  finish_constructor_body () ; 
 int /*<<< orphan*/  finish_destructor_body () ; 
 scalar_t__ processing_template_decl ; 

void
finish_function_body (tree compstmt)
{
  if (compstmt == NULL_TREE)
    return;

  /* Close the block.  */
  finish_compound_stmt (compstmt);

  if (processing_template_decl)
    /* Do nothing now.  */;
  else if (DECL_CONSTRUCTOR_P (current_function_decl))
    finish_constructor_body ();
  else if (DECL_DESTRUCTOR_P (current_function_decl))
    finish_destructor_body ();
}