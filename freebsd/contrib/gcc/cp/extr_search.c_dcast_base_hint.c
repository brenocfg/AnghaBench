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
struct dcast_data_s {scalar_t__ offset; int /*<<< orphan*/  repeated_base; scalar_t__ virt_depth; scalar_t__ subtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSTYPE_REPEATED_BASE_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  TYPE_BINFO (scalar_t__) ; 
 int /*<<< orphan*/  dfs_dcast_hint_post ; 
 int /*<<< orphan*/  dfs_dcast_hint_pre ; 
 int /*<<< orphan*/  dfs_walk_once_accessible (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dcast_data_s*) ; 
 scalar_t__ ssize_int (int) ; 

tree
dcast_base_hint (tree subtype, tree target)
{
  struct dcast_data_s data;

  data.subtype = subtype;
  data.virt_depth = 0;
  data.offset = NULL_TREE;
  data.repeated_base = CLASSTYPE_REPEATED_BASE_P (target);

  dfs_walk_once_accessible (TYPE_BINFO (target), /*friends=*/false,
			    dfs_dcast_hint_pre, dfs_dcast_hint_post, &data);
  return data.offset ? data.offset : ssize_int (-2);
}