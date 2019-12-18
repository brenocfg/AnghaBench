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

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ base_ctor_identifier ; 
 scalar_t__ base_dtor_identifier ; 
 scalar_t__ complete_ctor_identifier ; 
 scalar_t__ complete_dtor_identifier ; 
 scalar_t__ deleting_dtor_identifier ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ integer_one_node ; 
 scalar_t__ integer_three_node ; 
 scalar_t__ integer_two_node ; 
 scalar_t__ integer_zero_node ; 

tree
in_charge_arg_for_name (tree name)
{
 if (name == base_ctor_identifier
      || name == base_dtor_identifier)
    return integer_zero_node;
  else if (name == complete_ctor_identifier)
    return integer_one_node;
  else if (name == complete_dtor_identifier)
    return integer_two_node;
  else if (name == deleting_dtor_identifier)
    return integer_three_node;

  /* This function should only be called with one of the names listed
     above.  */
  gcc_unreachable ();
  return NULL_TREE;
}