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
 int /*<<< orphan*/  current_tinst_level ; 
 int /*<<< orphan*/  tree_last (int /*<<< orphan*/ ) ; 

tree
outermost_tinst_level (void)
{
  return tree_last (current_tinst_level);
}