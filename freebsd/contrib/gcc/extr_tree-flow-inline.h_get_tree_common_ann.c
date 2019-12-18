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
typedef  scalar_t__ tree_ann_common_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ create_tree_common_ann (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_common_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree_ann_common_t
get_tree_common_ann (tree t)
{
  tree_ann_common_t ann = tree_common_ann (t);
  return (ann) ? ann : create_tree_common_ann (t);
}