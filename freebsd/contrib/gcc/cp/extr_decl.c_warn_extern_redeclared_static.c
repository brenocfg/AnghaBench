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
 scalar_t__ CONST_DECL ; 
 scalar_t__ DECL_ARTIFICIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_STATIC_FUNCTION_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_THIS_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DECL ; 
 int /*<<< orphan*/  pedwarn (char*,int /*<<< orphan*/ ) ; 

void
warn_extern_redeclared_static (tree newdecl, tree olddecl)
{
  tree name;

  if (TREE_CODE (newdecl) == TYPE_DECL
      || TREE_CODE (newdecl) == TEMPLATE_DECL
      || TREE_CODE (newdecl) == CONST_DECL
      || TREE_CODE (newdecl) == NAMESPACE_DECL)
    return;

  /* Don't get confused by static member functions; that's a different
     use of `static'.  */
  if (TREE_CODE (newdecl) == FUNCTION_DECL
      && DECL_STATIC_FUNCTION_P (newdecl))
    return;

  /* If the old declaration was `static', or the new one isn't, then
     then everything is OK.  */
  if (DECL_THIS_STATIC (olddecl) || !DECL_THIS_STATIC (newdecl))
    return;

  /* It's OK to declare a builtin function as `static'.  */
  if (TREE_CODE (olddecl) == FUNCTION_DECL
      && DECL_ARTIFICIAL (olddecl))
    return;

  name = DECL_ASSEMBLER_NAME (newdecl);
  pedwarn ("%qD was declared %<extern%> and later %<static%>", newdecl);
  pedwarn ("previous declaration of %q+D", olddecl);
}