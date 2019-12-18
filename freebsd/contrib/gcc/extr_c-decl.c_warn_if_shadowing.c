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
struct c_binding {scalar_t__ decl; int /*<<< orphan*/  invisible; struct c_binding* shadowed; } ;

/* Variables and functions */
 scalar_t__ DECL_BUILT_IN (scalar_t__) ; 
 scalar_t__ DECL_FILE_SCOPE_P (scalar_t__) ; 
 scalar_t__ DECL_FROM_INLINE (scalar_t__) ; 
 scalar_t__ DECL_IS_BUILTIN (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 struct c_binding* I_SYMBOL_BINDING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_Wshadow ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  warn_shadow ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
warn_if_shadowing (tree new_decl)
{
  struct c_binding *b;

  /* Shadow warnings wanted?  */
  if (!warn_shadow
      /* No shadow warnings for internally generated vars.  */
      || DECL_IS_BUILTIN (new_decl)
      /* No shadow warnings for vars made for inlining.  */
      || DECL_FROM_INLINE (new_decl))
    return;

  /* Is anything being shadowed?  Invisible decls do not count.  */
  for (b = I_SYMBOL_BINDING (DECL_NAME (new_decl)); b; b = b->shadowed)
    if (b->decl && b->decl != new_decl && !b->invisible)
      {
	tree old_decl = b->decl;

	if (old_decl == error_mark_node)
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows previous "
		     "non-variable", new_decl);
	    break;
	  }
	else if (TREE_CODE (old_decl) == PARM_DECL)
	  warning (OPT_Wshadow, "declaration of %q+D shadows a parameter",
		   new_decl);
	else if (DECL_FILE_SCOPE_P (old_decl))
	  warning (OPT_Wshadow, "declaration of %q+D shadows a global "
		   "declaration", new_decl);
	else if (TREE_CODE (old_decl) == FUNCTION_DECL
		 && DECL_BUILT_IN (old_decl))
	  {
	    warning (OPT_Wshadow, "declaration of %q+D shadows "
		     "a built-in function", new_decl);
	    break;
	  }
	else
	  warning (OPT_Wshadow, "declaration of %q+D shadows a previous local",
		   new_decl);

	warning (OPT_Wshadow, "%Jshadowed declaration is here", old_decl);

	break;
      }
}