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
 scalar_t__ attribute_list_contained (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
attribute_list_equal (tree l1, tree l2)
{
  return attribute_list_contained (l1, l2)
	 && attribute_list_contained (l2, l1);
}