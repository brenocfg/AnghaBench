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
 int /*<<< orphan*/  COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TEMPLATE_TYPE_PARM ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ VOID_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  complete_type (scalar_t__) ; 
 int /*<<< orphan*/  cxx_incomplete_type_diagnostic (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ processing_template_decl ; 
 scalar_t__ same_type_p (scalar_t__,scalar_t__) ; 
 scalar_t__ tree_cons (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

tree
add_exception_specifier (tree list, tree spec, int complain)
{
  bool ok;
  tree core = spec;
  bool is_ptr;
  int diag_type = -1; /* none */

  if (spec == error_mark_node)
    return list;

  gcc_assert (spec && (!list || TREE_VALUE (list)));

  /* [except.spec] 1, type in an exception specifier shall not be
     incomplete, or pointer or ref to incomplete other than pointer
     to cv void.  */
  is_ptr = TREE_CODE (core) == POINTER_TYPE;
  if (is_ptr || TREE_CODE (core) == REFERENCE_TYPE)
    core = TREE_TYPE (core);
  if (complain < 0)
    ok = true;
  else if (VOID_TYPE_P (core))
    ok = is_ptr;
  else if (TREE_CODE (core) == TEMPLATE_TYPE_PARM)
    ok = true;
  else if (processing_template_decl)
    ok = true;
  else
    {
      ok = true;
      /* 15.4/1 says that types in an exception specifier must be complete,
	 but it seems more reasonable to only require this on definitions
	 and calls.  So just give a pedwarn at this point; we will give an
	 error later if we hit one of those two cases.  */
      if (!COMPLETE_TYPE_P (complete_type (core)))
	diag_type = 2; /* pedwarn */
    }

  if (ok)
    {
      tree probe;

      for (probe = list; probe; probe = TREE_CHAIN (probe))
	if (same_type_p (TREE_VALUE (probe), spec))
	  break;
      if (!probe)
	list = tree_cons (NULL_TREE, spec, list);
    }
  else
    diag_type = 0; /* error */

  if (diag_type >= 0 && complain)
    cxx_incomplete_type_diagnostic (NULL_TREE, core, diag_type);

  return list;
}