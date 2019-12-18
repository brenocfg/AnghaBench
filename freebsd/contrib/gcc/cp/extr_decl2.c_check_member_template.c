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
typedef  int DECL_IGNORED_P ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_TEMPLATE_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_VIRTUAL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ IS_AGGR_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DECL ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

void
check_member_template (tree tmpl)
{
  tree decl;

  gcc_assert (TREE_CODE (tmpl) == TEMPLATE_DECL);
  decl = DECL_TEMPLATE_RESULT (tmpl);

  if (TREE_CODE (decl) == FUNCTION_DECL
      || (TREE_CODE (decl) == TYPE_DECL
	  && IS_AGGR_TYPE (TREE_TYPE (decl))))
    {
      /* The parser rejects template declarations in local classes.  */
      gcc_assert (!current_function_decl);
      /* The parser rejects any use of virtual in a function template.  */
      gcc_assert (!(TREE_CODE (decl) == FUNCTION_DECL
		    && DECL_VIRTUAL_P (decl)));

      /* The debug-information generating code doesn't know what to do
	 with member templates.  */
      DECL_IGNORED_P (tmpl) = 1;
    }
  else
    error ("template declaration of %q#D", decl);
}