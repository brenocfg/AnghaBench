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
 scalar_t__ DERIVED_FROM_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_AGGR_TYPE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_type_ignoring_top_level_qualifiers_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
is_properly_derived_from (tree derived, tree base)
{
  if (!IS_AGGR_TYPE_CODE (TREE_CODE (derived))
      || !IS_AGGR_TYPE_CODE (TREE_CODE (base)))
    return false;

  /* We only allow proper derivation here.  The DERIVED_FROM_P macro
     considers every class derived from itself.  */
  return (!same_type_ignoring_top_level_qualifiers_p (derived, base)
	  && DERIVED_FROM_P (base, derived));
}