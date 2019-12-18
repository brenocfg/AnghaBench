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
struct TYPE_4__ {int /*<<< orphan*/  vars; } ;
typedef  TYPE_1__ dataflow_set ;

/* Variables and functions */
 int /*<<< orphan*/  dataflow_set_different_1 ; 
 int /*<<< orphan*/  dataflow_set_different_2 ; 
 int dataflow_set_different_value ; 
 int /*<<< orphan*/  htab_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
dataflow_set_different (dataflow_set *old_set, dataflow_set *new_set)
{
  dataflow_set_different_value = false;

  htab_traverse (old_set->vars, dataflow_set_different_1, new_set->vars);
  if (!dataflow_set_different_value)
    {
      /* We have compared the variables which are in both hash tables
	 so now only check whether there are some variables in NEW_SET->VARS
	 which are not in OLD_SET->VARS.  */
      htab_traverse (new_set->vars, dataflow_set_different_2, old_set->vars);
    }
  return dataflow_set_different_value;
}