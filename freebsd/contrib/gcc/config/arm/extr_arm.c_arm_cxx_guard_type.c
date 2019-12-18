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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ TARGET_AAPCS_BASED ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  long_long_integer_type_node ; 

__attribute__((used)) static tree
arm_cxx_guard_type (void)
{
  return TARGET_AAPCS_BASED ? integer_type_node : long_long_integer_type_node;
}