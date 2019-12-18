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
 scalar_t__ BINFO_VIRTUAL_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 

tree
binfo_from_vbase (tree binfo)
{
  for (; binfo; binfo = BINFO_INHERITANCE_CHAIN (binfo))
    {
      if (BINFO_VIRTUAL_P (binfo))
	return binfo;
    }
  return NULL_TREE;
}