#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* var_map ;
struct TYPE_4__ {struct TYPE_4__* ref_count; struct TYPE_4__* compact_to_partition; struct TYPE_4__* partition_to_compact; int /*<<< orphan*/  var_partition; struct TYPE_4__* partition_to_var; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  partition_delete (int /*<<< orphan*/ ) ; 

void
delete_var_map (var_map map)
{
  free (map->partition_to_var);
  partition_delete (map->var_partition);
  if (map->partition_to_compact)
    free (map->partition_to_compact);
  if (map->compact_to_partition)
    free (map->compact_to_partition);
  if (map->ref_count)
    free (map->ref_count);
  free (map);
}