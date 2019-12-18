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
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  DECL_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_PARM_P (scalar_t__) ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ TEMPLATE_PARMS_FOR_INLINE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  current_template_parms ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ innermost_non_namespace_value (int /*<<< orphan*/ ) ; 

void
check_template_shadow (tree decl)
{
  tree olddecl;

  /* If we're not in a template, we can't possibly shadow a template
     parameter.  */
  if (!current_template_parms)
    return;

  /* Figure out what we're shadowing.  */
  if (TREE_CODE (decl) == OVERLOAD)
    decl = OVL_CURRENT (decl);
  olddecl = innermost_non_namespace_value (DECL_NAME (decl));

  /* If there's no previous binding for this name, we're not shadowing
     anything, let alone a template parameter.  */
  if (!olddecl)
    return;

  /* If we're not shadowing a template parameter, we're done.  Note
     that OLDDECL might be an OVERLOAD (or perhaps even an
     ERROR_MARK), so we can't just blithely assume it to be a _DECL
     node.  */
  if (!DECL_P (olddecl) || !DECL_TEMPLATE_PARM_P (olddecl))
    return;

  /* We check for decl != olddecl to avoid bogus errors for using a
     name inside a class.  We check TPFI to avoid duplicate errors for
     inline member templates.  */
  if (decl == olddecl
      || TEMPLATE_PARMS_FOR_INLINE (current_template_parms))
    return;

  error ("declaration of %q+#D", decl);
  error (" shadows template parm %q+#D", olddecl);
}