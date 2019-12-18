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

__attribute__((used)) static int
is_subobject_of_p (tree parent, tree binfo)
{
  tree probe;

  for (probe = parent; probe; probe = BINFO_INHERITANCE_CHAIN (probe))
    {
      if (probe == binfo)
	return 1;
      if (BINFO_VIRTUAL_P (probe))
	return (binfo_for_vbase (BINFO_TYPE (probe), BINFO_TYPE (binfo))
		!= NULL_TREE);
    }
  return 0;
}