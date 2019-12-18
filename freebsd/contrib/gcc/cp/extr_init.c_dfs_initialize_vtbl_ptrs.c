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
 int /*<<< orphan*/  BINFO_PRIMARY_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ BINFO_VIRTUAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CONTAINS_VPTR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_base_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dfs_skip_bases ; 
 int /*<<< orphan*/  expand_virtual_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
dfs_initialize_vtbl_ptrs (tree binfo, void *data)
{
  if (!TYPE_CONTAINS_VPTR_P (BINFO_TYPE (binfo)))
    return dfs_skip_bases;

  if (!BINFO_PRIMARY_P (binfo) || BINFO_VIRTUAL_P (binfo))
    {
      tree base_ptr = TREE_VALUE ((tree) data);

      base_ptr = build_base_path (PLUS_EXPR, base_ptr, binfo, /*nonnull=*/1);

      expand_virtual_init (binfo, base_ptr);
    }

  return NULL_TREE;
}