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
 scalar_t__ processing_template_decl ; 
 int /*<<< orphan*/  save_expr (int /*<<< orphan*/ ) ; 

tree
cp_save_expr (tree expr)
{
  /* There is no reason to create a SAVE_EXPR within a template; if
     needed, we can create the SAVE_EXPR when instantiating the
     template.  Furthermore, the middle-end cannot handle C++-specific
     tree codes.  */
  if (processing_template_decl)
    return expr;
  return save_expr (expr);
}