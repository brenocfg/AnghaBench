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
 scalar_t__ ANON_AGGR_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SELF_REFERENCE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int accessible_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
accessible_base_p (tree t, tree base, bool consider_local_p)
{
  tree decl;

  /* [class.access.base]

     A base class is said to be accessible if an invented public
     member of the base class is accessible.

     If BASE is a non-proper base, this condition is trivially
     true.  */
  if (same_type_p (t, base))
    return true;
  /* Rather than inventing a public member, we use the implicit
     public typedef created in the scope of every class.  */
  decl = TYPE_FIELDS (base);
  while (!DECL_SELF_REFERENCE_P (decl))
    decl = TREE_CHAIN (decl);
  while (ANON_AGGR_TYPE_P (t))
    t = TYPE_CONTEXT (t);
  return accessible_p (t, decl, consider_local_p);
}