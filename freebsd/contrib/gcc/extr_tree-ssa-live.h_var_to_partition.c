#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* var_map ;
typedef  TYPE_2__* var_ann_t ;
typedef  int /*<<< orphan*/  tree ;
struct TYPE_7__ {scalar_t__ out_of_ssa_tag; } ;
struct TYPE_6__ {int* partition_to_compact; int /*<<< orphan*/  var_partition; } ;

/* Variables and functions */
 int NO_PARTITION ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int VAR_ANN_PARTITION (TYPE_2__*) ; 
 int partition_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* var_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
var_to_partition (var_map map, tree var)
{
  var_ann_t ann;
  int part;

  if (TREE_CODE (var) == SSA_NAME)
    {
      part = partition_find (map->var_partition, SSA_NAME_VERSION (var));
      if (map->partition_to_compact)
	part = map->partition_to_compact[part];
    }
  else
    {
      ann = var_ann (var);
      if (ann->out_of_ssa_tag)
	part = VAR_ANN_PARTITION (ann);
      else
        part = NO_PARTITION;
    }
  return part;
}