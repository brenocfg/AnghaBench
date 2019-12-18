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

/* Variables and functions */
 int /*<<< orphan*/  dw2_output_indirect_constant_1 ; 
 scalar_t__ indirect_pool ; 
 int /*<<< orphan*/  splay_tree_foreach (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dw2_output_indirect_constants (void)
{
  if (indirect_pool)
    splay_tree_foreach (indirect_pool, dw2_output_indirect_constant_1, NULL);
}