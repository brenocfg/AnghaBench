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
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTR_P (scalar_t__) ; 
 int /*<<< orphan*/  ba_check ; 
 int /*<<< orphan*/  ba_unique ; 
 scalar_t__ build_base_path (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ lookup_base (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

tree
convert_to_base (tree object, tree type, bool check_access, bool nonnull)
{
  tree binfo;
  tree object_type;

  if (TYPE_PTR_P (TREE_TYPE (object)))
    {
      object_type = TREE_TYPE (TREE_TYPE (object));
      type = TREE_TYPE (type);
    }
  else
    object_type = TREE_TYPE (object);

  binfo = lookup_base (object_type, type,
		       check_access ? ba_check : ba_unique,
		       NULL);
  if (!binfo || binfo == error_mark_node)
    return error_mark_node;

  return build_base_path (PLUS_EXPR, object, binfo, nonnull);
}