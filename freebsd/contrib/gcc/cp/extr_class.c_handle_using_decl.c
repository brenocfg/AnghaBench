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
 int /*<<< orphan*/  DECL_ARTIFICIAL (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TREE_PRIVATE (scalar_t__) ; 
 scalar_t__ TREE_PROTECTED (scalar_t__) ; 
 scalar_t__ USING_DECL_DECLS (scalar_t__) ; 
 int /*<<< orphan*/  USING_DECL_SCOPE (scalar_t__) ; 
 scalar_t__ access_private_node ; 
 scalar_t__ access_protected_node ; 
 scalar_t__ access_public_node ; 
 int /*<<< orphan*/  add_method (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  alter_access (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cp_emit_debug_info_for_using (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ is_overloaded_fn (scalar_t__) ; 
 scalar_t__ lookup_member (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  processing_template_decl ; 

__attribute__((used)) static void
handle_using_decl (tree using_decl, tree t)
{
  tree decl = USING_DECL_DECLS (using_decl);
  tree name = DECL_NAME (using_decl);
  tree access
    = TREE_PRIVATE (using_decl) ? access_private_node
    : TREE_PROTECTED (using_decl) ? access_protected_node
    : access_public_node;
  tree flist = NULL_TREE;
  tree old_value;

  gcc_assert (!processing_template_decl && decl);

  old_value = lookup_member (t, name, /*protect=*/0, /*want_type=*/false);
  if (old_value)
    {
      if (is_overloaded_fn (old_value))
	old_value = OVL_CURRENT (old_value);

      if (DECL_P (old_value) && DECL_CONTEXT (old_value) == t)
	/* OK */;
      else
	old_value = NULL_TREE;
    }

  cp_emit_debug_info_for_using (decl, USING_DECL_SCOPE (using_decl));

  if (is_overloaded_fn (decl))
    flist = decl;

  if (! old_value)
    ;
  else if (is_overloaded_fn (old_value))
    {
      if (flist)
	/* It's OK to use functions from a base when there are functions with
	   the same name already present in the current class.  */;
      else
	{
	  error ("%q+D invalid in %q#T", using_decl, t);
	  error ("  because of local method %q+#D with same name",
		 OVL_CURRENT (old_value));
	  return;
	}
    }
  else if (!DECL_ARTIFICIAL (old_value))
    {
      error ("%q+D invalid in %q#T", using_decl, t);
      error ("  because of local member %q+#D with same name", old_value);
      return;
    }

  /* Make type T see field decl FDECL with access ACCESS.  */
  if (flist)
    for (; flist; flist = OVL_NEXT (flist))
      {
	add_method (t, OVL_CURRENT (flist), using_decl);
	alter_access (t, OVL_CURRENT (flist), access);
      }
  else
    alter_access (t, decl, access);
}