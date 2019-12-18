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
struct TYPE_3__ {int* compact_to_partition; int /*<<< orphan*/ * partition_to_var; int /*<<< orphan*/  var_partition; } ;

/* Variables and functions */
 int partition_find (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline tree
partition_to_var (var_map map, int i)
{
  if (map->compact_to_partition)
    i = map->compact_to_partition[i];
  i = partition_find (map->var_partition, i);
  return map->partition_to_var[i];
}