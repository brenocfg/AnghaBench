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
 int /*<<< orphan*/  CLASSTYPE_VBASECLASSES (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  SAME_BINFO_TYPE_P (int /*<<< orphan*/ ,scalar_t__) ; 

tree
binfo_via_virtual (tree binfo, tree limit)
{
  if (limit && !CLASSTYPE_VBASECLASSES (limit))
    /* LIMIT has no virtual bases, so BINFO cannot be via one.  */
    return NULL_TREE;

  for (; binfo && !SAME_BINFO_TYPE_P (BINFO_TYPE (binfo), limit);
       binfo = BINFO_INHERITANCE_CHAIN (binfo))
    {
      if (BINFO_VIRTUAL_P (binfo))
	return binfo;
    }
  return NULL_TREE;
}