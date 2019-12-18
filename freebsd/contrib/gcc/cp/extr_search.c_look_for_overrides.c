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
 scalar_t__ BINFO_BASE_ITERATE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_BINFO (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_POLYMORPHIC_P (int /*<<< orphan*/ ) ; 
 scalar_t__ look_for_overrides_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
look_for_overrides (tree type, tree fndecl)
{
  tree binfo = TYPE_BINFO (type);
  tree base_binfo;
  int ix;
  int found = 0;

  for (ix = 0; BINFO_BASE_ITERATE (binfo, ix, base_binfo); ix++)
    {
      tree basetype = BINFO_TYPE (base_binfo);

      if (TYPE_POLYMORPHIC_P (basetype))
	found += look_for_overrides_r (basetype, fndecl);
    }
  return found;
}