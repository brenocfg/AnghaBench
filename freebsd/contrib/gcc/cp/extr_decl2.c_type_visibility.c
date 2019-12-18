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
 int VISIBILITY_DEFAULT ; 
 int /*<<< orphan*/  min_vis_r ; 
 int /*<<< orphan*/  walk_tree_without_duplicates (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
type_visibility (tree type)
{
  int vis = VISIBILITY_DEFAULT;
  walk_tree_without_duplicates (&type, min_vis_r, &vis);
  return vis;
}