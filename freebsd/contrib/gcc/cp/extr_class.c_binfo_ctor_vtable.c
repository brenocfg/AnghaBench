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
 int /*<<< orphan*/  BINFO_VTABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_BINFO ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_LIST ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
binfo_ctor_vtable (tree binfo)
{
  tree vt;

  while (1)
    {
      vt = BINFO_VTABLE (binfo);
      if (TREE_CODE (vt) == TREE_LIST)
	vt = TREE_VALUE (vt);
      if (TREE_CODE (vt) == TREE_BINFO)
	binfo = vt;
      else
	break;
    }

  return vt;
}