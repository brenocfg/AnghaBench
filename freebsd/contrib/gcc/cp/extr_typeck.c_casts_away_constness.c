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
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_POINTED_TO_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  casts_away_constness_r (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
casts_away_constness (tree t1, tree t2)
{
  if (TREE_CODE (t2) == REFERENCE_TYPE)
    {
      /* [expr.const.cast]

	 Casting from an lvalue of type T1 to an lvalue of type T2
	 using a reference cast casts away constness if a cast from an
	 rvalue of type "pointer to T1" to the type "pointer to T2"
	 casts away constness.  */
      t1 = (TREE_CODE (t1) == REFERENCE_TYPE ? TREE_TYPE (t1) : t1);
      return casts_away_constness (build_pointer_type (t1),
				   build_pointer_type (TREE_TYPE (t2)));
    }

  if (TYPE_PTRMEM_P (t1) && TYPE_PTRMEM_P (t2))
    /* [expr.const.cast]

       Casting from an rvalue of type "pointer to data member of X
       of type T1" to the type "pointer to data member of Y of type
       T2" casts away constness if a cast from an rvalue of type
       "pointer to T1" to the type "pointer to T2" casts away
       constness.  */
    return casts_away_constness
      (build_pointer_type (TYPE_PTRMEM_POINTED_TO_TYPE (t1)),
       build_pointer_type (TYPE_PTRMEM_POINTED_TO_TYPE (t2)));

  /* Casting away constness is only something that makes sense for
     pointer or reference types.  */
  if (TREE_CODE (t1) != POINTER_TYPE
      || TREE_CODE (t2) != POINTER_TYPE)
    return false;

  /* Top-level qualifiers don't matter.  */
  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);
  casts_away_constness_r (&t1, &t2);
  if (!can_convert (t2, t1))
    return true;

  return false;
}