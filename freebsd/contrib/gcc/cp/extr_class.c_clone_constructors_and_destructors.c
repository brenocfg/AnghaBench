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
 scalar_t__ CLASSTYPE_CONSTRUCTORS (scalar_t__) ; 
 scalar_t__ CLASSTYPE_DESTRUCTORS (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_METHOD_VEC (scalar_t__) ; 
 int /*<<< orphan*/  OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 int /*<<< orphan*/  clone_function_decl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
clone_constructors_and_destructors (tree t)
{
  tree fns;

  /* If for some reason we don't have a CLASSTYPE_METHOD_VEC, we bail
     out now.  */
  if (!CLASSTYPE_METHOD_VEC (t))
    return;

  for (fns = CLASSTYPE_CONSTRUCTORS (t); fns; fns = OVL_NEXT (fns))
    clone_function_decl (OVL_CURRENT (fns), /*update_method_vec_p=*/1);
  for (fns = CLASSTYPE_DESTRUCTORS (t); fns; fns = OVL_NEXT (fns))
    clone_function_decl (OVL_CURRENT (fns), /*update_method_vec_p=*/1);
}