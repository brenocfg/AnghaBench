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
struct TYPE_3__ {int* ref_count; } ;

/* Variables and functions */
 int SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int*) ; 

__attribute__((used)) static inline int
version_ref_count (var_map map, tree ssa_var)
{
  int version = SSA_NAME_VERSION (ssa_var);
  gcc_assert (map->ref_count);
  return map->ref_count[version];
}