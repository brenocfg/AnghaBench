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
struct c_binding {int /*<<< orphan*/  decl; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 scalar_t__ B_IN_CURRENT_SCOPE (struct c_binding*) ; 
 scalar_t__ B_IN_EXTERNAL_SCOPE (struct c_binding*) ; 
 struct c_binding* I_TAG_BINDING (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ current_scope ; 
 scalar_t__ file_scope ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  pending_invalid_xref ; 
 int /*<<< orphan*/  pending_invalid_xref_location ; 
 int /*<<< orphan*/  pending_xref_error () ; 

__attribute__((used)) static tree
lookup_tag (enum tree_code code, tree name, int thislevel_only)
{
  struct c_binding *b = I_TAG_BINDING (name);
  int thislevel = 0;

  if (!b || !b->decl)
    return 0;

  /* We only care about whether it's in this level if
     thislevel_only was set or it might be a type clash.  */
  if (thislevel_only || TREE_CODE (b->decl) != code)
    {
      /* For our purposes, a tag in the external scope is the same as
	 a tag in the file scope.  (Primarily relevant to Objective-C
	 and its builtin structure tags, which get pushed before the
	 file scope is created.)  */
      if (B_IN_CURRENT_SCOPE (b)
	  || (current_scope == file_scope && B_IN_EXTERNAL_SCOPE (b)))
	thislevel = 1;
    }

  if (thislevel_only && !thislevel)
    return 0;

  if (TREE_CODE (b->decl) != code)
    {
      /* Definition isn't the kind we were looking for.  */
      pending_invalid_xref = name;
      pending_invalid_xref_location = input_location;

      /* If in the same binding level as a declaration as a tag
	 of a different type, this must not be allowed to
	 shadow that tag, so give the error immediately.
	 (For example, "struct foo; union foo;" is invalid.)  */
      if (thislevel)
	pending_xref_error ();
    }
  return b->decl;
}