#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* var_map ;
typedef  scalar_t__ tree ;
struct TYPE_5__ {int* compact_to_partition; int* partition_to_compact; int /*<<< orphan*/  var_partition; } ;

/* Variables and functions */
 scalar_t__ DECL_IGNORED_P (scalar_t__) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 int NO_PARTITION ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  change_partition_var (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int partition_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int partition_union (int /*<<< orphan*/ ,int,int) ; 
 int var_to_partition (TYPE_1__*,scalar_t__) ; 

int
var_union (var_map map, tree var1, tree var2)
{
  int p1, p2, p3;
  tree root_var = NULL_TREE;
  tree other_var = NULL_TREE;

  /* This is independent of partition_to_compact. If partition_to_compact is 
     on, then whichever one of these partitions is absorbed will never have a
     dereference into the partition_to_compact array any more.  */

  if (TREE_CODE (var1) == SSA_NAME)
    p1 = partition_find (map->var_partition, SSA_NAME_VERSION (var1));
  else
    {
      p1 = var_to_partition (map, var1);
      if (map->compact_to_partition)
        p1 = map->compact_to_partition[p1];
      root_var = var1;
    }
  
  if (TREE_CODE (var2) == SSA_NAME)
    p2 = partition_find (map->var_partition, SSA_NAME_VERSION (var2));
  else
    {
      p2 = var_to_partition (map, var2);
      if (map->compact_to_partition)
        p2 = map->compact_to_partition[p2];

      /* If there is no root_var set, or it's not a user variable, set the
	 root_var to this one.  */
      if (!root_var || (DECL_P (root_var) && DECL_IGNORED_P (root_var)))
        {
	  other_var = root_var;
	  root_var = var2;
	}
      else 
	other_var = var2;
    }

  gcc_assert (p1 != NO_PARTITION);
  gcc_assert (p2 != NO_PARTITION);

  if (p1 == p2)
    p3 = p1;
  else
    p3 = partition_union (map->var_partition, p1, p2);

  if (map->partition_to_compact)
    p3 = map->partition_to_compact[p3];

  if (root_var)
    change_partition_var (map, root_var, p3);
  if (other_var)
    change_partition_var (map, other_var, p3);

  return p3;
}