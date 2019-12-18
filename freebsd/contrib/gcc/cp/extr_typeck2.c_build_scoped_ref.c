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
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  ba_check ; 
 scalar_t__ build_base_path (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  error_not_base_type (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_base (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

tree
build_scoped_ref (tree datum, tree basetype, tree* binfo_p)
{
  tree binfo;

  if (datum == error_mark_node)
    return error_mark_node;
  if (*binfo_p)
    binfo = *binfo_p;
  else
    binfo = lookup_base (TREE_TYPE (datum), basetype, ba_check, NULL);

  if (!binfo || binfo == error_mark_node)
    {
      *binfo_p = NULL_TREE;
      if (!binfo)
	error_not_base_type (basetype, TREE_TYPE (datum));
      return error_mark_node;
    }

  *binfo_p = binfo;
  return build_base_path (PLUS_EXPR, datum, binfo, 1);
}