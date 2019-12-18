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
typedef  int /*<<< orphan*/  histogram_values ;

/* Variables and functions */
 scalar_t__ flag_value_profile_transformations ; 
 int /*<<< orphan*/  tree_divmod_values_to_profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tree_values_to_profile (tree stmt, histogram_values *values)
{
  if (flag_value_profile_transformations)
    tree_divmod_values_to_profile (stmt, values);
}