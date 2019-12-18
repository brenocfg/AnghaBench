#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* var_map ;
typedef  int /*<<< orphan*/  tree ;
struct _var_map {int dummy; } ;
struct TYPE_3__ {int num_partitions; int partition_size; int /*<<< orphan*/ * ref_count; int /*<<< orphan*/ * compact_to_partition; int /*<<< orphan*/ * partition_to_compact; int /*<<< orphan*/ * partition_to_var; int /*<<< orphan*/  var_partition; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  partition_new (int) ; 
 scalar_t__ xmalloc (int) ; 

var_map
init_var_map (int size)
{
  var_map map;

  map = (var_map) xmalloc (sizeof (struct _var_map));
  map->var_partition = partition_new (size);
  map->partition_to_var 
	      = (tree *)xmalloc (size * sizeof (tree));
  memset (map->partition_to_var, 0, size * sizeof (tree));

  map->partition_to_compact = NULL;
  map->compact_to_partition = NULL;
  map->num_partitions = size;
  map->partition_size = size;
  map->ref_count = NULL;
  return map;
}