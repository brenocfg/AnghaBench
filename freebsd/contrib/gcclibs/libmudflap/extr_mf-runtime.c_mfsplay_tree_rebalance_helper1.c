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
typedef  int /*<<< orphan*/  mfsplay_tree_node ;

/* Variables and functions */

__attribute__((used)) static int
mfsplay_tree_rebalance_helper1 (mfsplay_tree_node n, void *array_ptr)
{
  mfsplay_tree_node **p = array_ptr;
  *(*p) = n;
  (*p)++;
  return 0;
}