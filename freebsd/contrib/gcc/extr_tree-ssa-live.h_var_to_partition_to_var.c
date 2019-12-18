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
typedef  int /*<<< orphan*/  var_map ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int NO_PARTITION ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  partition_to_var (int /*<<< orphan*/ ,int) ; 
 int var_to_partition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree
var_to_partition_to_var (var_map map, tree var)
{
  int part;

  part = var_to_partition (map, var);
  if (part == NO_PARTITION)
    return NULL_TREE;
  return partition_to_var (map, part);
}