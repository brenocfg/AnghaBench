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
 scalar_t__ BINFO_INHERITANCE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_TYPE (scalar_t__) ; 
 scalar_t__ BINFO_VIRTUAL_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ binfo_for_vbase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
base_derived_from (tree derived, tree base)
{
  tree probe;

  for (probe = base; probe; probe = BINFO_INHERITANCE_CHAIN (probe))
    {
      if (probe == derived)
	return true;
      else if (BINFO_VIRTUAL_P (probe))
	/* If we meet a virtual base, we can't follow the inheritance
	   any more.  See if the complete type of DERIVED contains
	   such a virtual base.  */
	return (binfo_for_vbase (BINFO_TYPE (probe), BINFO_TYPE (derived))
		!= NULL_TREE);
    }
  return false;
}