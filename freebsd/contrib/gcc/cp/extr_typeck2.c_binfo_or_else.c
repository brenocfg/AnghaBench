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
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  ba_unique ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  error_not_base_type (scalar_t__,scalar_t__) ; 
 scalar_t__ lookup_base (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

tree
binfo_or_else (tree base, tree type)
{
  tree binfo = lookup_base (type, base, ba_unique, NULL);

  if (binfo == error_mark_node)
    return NULL_TREE;
  else if (!binfo)
    error_not_base_type (base, type);
  return binfo;
}