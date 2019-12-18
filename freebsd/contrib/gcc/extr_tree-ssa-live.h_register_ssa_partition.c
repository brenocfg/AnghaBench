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
typedef  scalar_t__ tree ;
struct TYPE_3__ {scalar_t__* partition_to_var; int /*<<< orphan*/ * ref_count; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 size_t SSA_NAME_VERSION (scalar_t__) ; 
 int /*<<< orphan*/  register_ssa_partition_check (scalar_t__) ; 

__attribute__((used)) static inline void
register_ssa_partition (var_map map, tree ssa_var, bool is_use)
{
  int version;

#if defined ENABLE_CHECKING
  register_ssa_partition_check (ssa_var);
#endif

  version = SSA_NAME_VERSION (ssa_var);
  if (is_use && map->ref_count)
    map->ref_count[version]++;

  if (map->partition_to_var[version] == NULL_TREE)
    map->partition_to_var[SSA_NAME_VERSION (ssa_var)] = ssa_var;
}